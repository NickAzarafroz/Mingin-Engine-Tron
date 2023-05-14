#pragma once
#include "SoundSystem.h"
#include "AudioClip.h"
#include <cassert>
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
		}

		void Update() override
		{
			// If there are no pending requests, do nothing.
			if (m_Head == m_Tail) return;

			if(!m_pAudio->IsLoaded())
			{
				m_pAudio->Load(m_Pending[m_Head].id);
				m_pAudio->SetVolume(m_Pending[m_Head].volume);
				m_pAudio->Play();
			}

			m_Head = (m_Head + 1) % MAX_PENDING;
		}

		void Play(const Sound_ID id, const float volume) override
		{
			assert((m_Tail + 1) % MAX_PENDING != m_Head);

			// Add to the end of the list.
			m_Pending[m_Tail].id = id;
			m_Pending[m_Tail].volume = volume;
			m_Tail = (m_Tail + 1) % MAX_PENDING;
		}

	private:
		static const int MAX_PENDING = 16;

		static SoundPlay m_Pending[MAX_PENDING];
		static int m_Head;
		static int m_Tail;
		AudioClip* m_pAudio;
	};

	SoundPlay PrimarySoundSystem::m_Pending[MAX_PENDING];
	int PrimarySoundSystem::m_Head = 0;
	int PrimarySoundSystem::m_Tail = 0;
}