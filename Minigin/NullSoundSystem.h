#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		virtual void Init() override {}
		virtual void Update() override {}
		virtual void Play(const Sound_ID, const float) override {}
		virtual void Release() override {}
	};
}