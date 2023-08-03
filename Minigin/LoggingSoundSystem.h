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
			std::cout << "Initialise Soundsystem\n";
			m_pReal_SS->Init();
		}

		virtual void Update() override 
		{
			//std::cout << "Updating ...\n";
			m_pReal_SS->Update();
		}

		void Play(const SoundFile filePath, const float volume) override 
		{
			std::cout << "Playing " << filePath << " at volume " << volume << std::endl;
			m_pReal_SS->Play(filePath, volume);
		}

		virtual void Release() override 
		{
			std::cout << "Release ...\n";
			m_pReal_SS->Release();
		}

	private:
		std::unique_ptr<SoundSystem> m_pReal_SS;
	};
}