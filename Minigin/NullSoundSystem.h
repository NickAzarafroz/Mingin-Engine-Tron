#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		void Play(const Sound_id, const float) override {}
	};
}