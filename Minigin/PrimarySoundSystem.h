#pragma once
#include "SoundSystem.h"
namespace dae
{
	class PrimarySoundSystem final : public SoundSystem
	{
	public:
		void Play(const Sound_id id, const float volume) override
		{
			// lots of sdl_mixer code
		}
	};
}