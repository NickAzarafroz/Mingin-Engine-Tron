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

		virtual void Init() override 
		{
			m_pReal_SS->Init();
			std::cout << "Initialise Sound\n";
		}

		virtual void Update() override 
		{
			m_pReal_SS->Update();
			std::cout << "Updating ...\n";
		}

		void Play(const Sound_ID id, const float volume) override 
		{
			m_pReal_SS->Play(id, volume);
			std::cout << "Playing " << id << " at volume " << volume << std::endl;
		}

	private:
		std::unique_ptr<SoundSystem> m_pReal_SS;
	};
}