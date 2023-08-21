#pragma once
#include "SoundSystem.h"

namespace dae
{
	class NullSoundSystem final : public SoundSystem
	{
		virtual void Init() override {}
		virtual void Update() override {}
		virtual void Play(const SoundFile, const float, int) override {}
		virtual void Stop() override {}
		virtual void Release() override {}
	};
}