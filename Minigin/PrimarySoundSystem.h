#pragma once
#include "SoundSystem.h"
namespace dae
{
	struct PlayMessage
	{
		Sound_ID id;
		int volume;
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

			// lots of sdl_mixer code

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

		static PlayMessage m_Pending[MAX_PENDING];
		static int m_Head;
		static int m_Tail;
	};
}