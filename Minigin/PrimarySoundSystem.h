#pragma once
#include "SoundSystem.h"
#include "AudioClip.h"
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace dae
{
	struct SoundPlay
	{
		Sound_ID id;
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
		}

		void Update() override
		{
			// Do nothing - sound requests are now processed on a separate thread
		}

		void Play(const Sound_ID id, const float volume) override
		{
			std::unique_lock<std::mutex> lock(m_Mutex);

			// If the buffer is full, wait for the sound thread to process some requests
			while ((m_Tail + 1) % MAX_PENDING == m_Head)
			{
				m_CV.wait(lock);
			}

			// Add to the end of the list.
			m_Pending[m_Tail].id = id;
			m_Pending[m_Tail].volume = volume;
			m_Tail = (m_Tail + 1) % MAX_PENDING;

			// Notify the sound thread that a new sound request is pending
			m_CV.notify_one();
		}

	private:
		static const int MAX_PENDING = 16;

		static SoundPlay m_Pending[MAX_PENDING];
		static int m_Head;
		static int m_Tail;
		AudioClip* m_pAudio;

		std::jthread m_SoundThread;
		std::mutex m_Mutex;
		std::condition_variable m_CV;

		void SoundThread()
		{
			while (true)
			{
				// Check the ring buffer for pending sound requests
				if (m_Head != m_Tail)
				{
					// Load and play the audio clip
					m_pAudio->Load(m_Pending[m_Head].id);
					m_pAudio->SetVolume(m_Pending[m_Head].volume);
					m_pAudio->Play();

					m_Head = (m_Head + 1) % MAX_PENDING;

					// Notify the main thread that the buffer is no longer full
					m_CV.notify_one();
				}
				else
				{
					// Sleep for a short amount of time if the buffer is empty
					std::this_thread::sleep_for(std::chrono::milliseconds(10));
				}
			}
		}
	};

	SoundPlay PrimarySoundSystem::m_Pending[MAX_PENDING];
	int PrimarySoundSystem::m_Head = 0;
	int PrimarySoundSystem::m_Tail = 0;
}