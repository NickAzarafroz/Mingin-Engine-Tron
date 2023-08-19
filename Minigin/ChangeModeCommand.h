#pragma once
#include "GameActorCommand.h"
#include <array>
namespace dae
{
	class ChangeModeCommand : public GameActorCommand
	{
	public:
		ChangeModeCommand(GameObject* actor, std::array<std::string, 3> modes) : GameActorCommand(actor), m_Modes{modes} {}
		virtual ~ChangeModeCommand() = default;

		ChangeModeCommand(const ChangeModeCommand& other) = delete;
		ChangeModeCommand(ChangeModeCommand&& other) = delete;
		ChangeModeCommand& operator=(const ChangeModeCommand& other) = delete;
		ChangeModeCommand& operator=(ChangeModeCommand&& other) = delete;

		void Execute() override;

		static int m_ModeIndex;

	private:
		std::array<std::string, 3> m_Modes{};
	};
}

