#pragma once
#include "SoundSystem.h"
#include "AudioClip.h"
#include <thread>
#include <mutex>
#include <condition_variable>

namespace dae
{
	struct SoundPlay
	{
		SoundFile filePath;
		float volume;
	};

	class PrimarySoundSystem final : public SoundSystem
	{
	public:
		void Init() override
		{
			m_Head = 0;
			m_Tail = 0;

			// Create a new thread to process sound requests
			m_SoundThread = std::jthread(&PrimarySoundSystem::SoundThread, this);
			m_pAudio = std::make_unique<AudioClip>();
		}

		void Update() override
		{
			if(!m_DoContinue)
			{
				m_CV.notify_one();
			}
		}

		void Play(const SoundFile filePath, const float volume, int loop) override
		{
			m_Loop = loop;

			// If the buffer is full, drop the sound request
			while ((m_Tail + 1) % MAX_PENDING == m_Head)
			{
				return;
			}

			// Add to the end of the list.
			m_Pending[m_Tail].filePath = filePath;
			m_Pending[m_Tail].volume = volume;
			m_Tail = (m_Tail + 1) % MAX_PENDING;

			// Notify the sound thread that a new sound request is pending
			m_CV.notify_one();
		}

		void Stop()
		{
			m_pAudio->Stop();
		}

		void Release() override
		{
			m_DoContinue = false;
		}

	private:
		static const int MAX_PENDING = 16;

		static SoundPlay m_Pending[MAX_PENDING];
		static int m_Head;
		static int m_Tail;
		static bool m_DoContinue;
		
		int m_Loop;
		std::unique_ptr<AudioClip> m_pAudio;

		std::jthread m_SoundThread;
		std::mutex m_Mutex;
		std::condition_variable m_CV;

		void SoundThread()
		{
			while (m_DoContinue)
			{
				std::unique_lock<std::mutex> lock(m_Mutex);

				// Wait until there are pending sound requests in the buffer
				m_CV.wait(lock, [this]() 
					{ 
						return ((m_Head != m_Tail) || !m_DoContinue);
					});

				if(!m_DoContinue)
				{
					return;
				}

				// Load and play the audio clip
				m_pAudio->Load(m_Pending[m_Head].filePath);
				m_pAudio->SetVolume(m_Pending[m_Head].volume);
				m_pAudio->Play(m_Loop);

				m_Head = (m_Head + 1) % MAX_PENDING;
			}
		}
	};

	SoundPlay PrimarySoundSystem::m_Pending[MAX_PENDING];
	int PrimarySoundSystem::m_Head = 0;
	int PrimarySoundSystem::m_Tail = 0;
	bool PrimarySoundSystem::m_DoContinue = true;
}