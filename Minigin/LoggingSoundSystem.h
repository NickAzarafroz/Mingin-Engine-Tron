#pragma once
#include <iostream>
#include "SoundSystem.h"
namespace dae
{
	class LoggingSoundSystem final : public SoundSystem
	{
	public:
		LoggingSoundSystem(std::unique_ptr<SoundSystem>&& ss) : m_pReal_SS(std::move(ss)) {}
		virtual ~LoggingSoundSystem() = default;

		void Play(const Sound_id id, const float volume) override 
		{
			m_pReal_SS->Play(id, volume);
			std::cout << "Playing " << id << " at volume " << volume << std::endl;
		}

	private:
		std::unique_ptr<SoundSystem> m_pReal_SS;
	};
}