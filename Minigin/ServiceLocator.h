#pragma once
#include <memory>
#include "SoundSystem.h"
#include "NullSoundSystem.h"

namespace dae
{
	class ServiceLocator final
	{
	public:
		static SoundSystem& GetSoundSystem() { return *m_pSS_Instance; }
		static void RegisterSoundSystem(std::unique_ptr<SoundSystem>&& ss)
		{
			m_pSS_Instance = ss == nullptr ? std::make_unique<NullSoundSystem>() : std::move(ss);
		}

	private:
		static std::unique_ptr<SoundSystem> m_pSS_Instance;
	};

	std::unique_ptr<SoundSystem> ServiceLocator::m_pSS_Instance{ std::make_unique<NullSoundSystem>() };
}