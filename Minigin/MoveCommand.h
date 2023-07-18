#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class MoveCommand : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* actor, float speed, glm::vec2 dir) : GameActorCommand(actor), m_Speed{ speed }, m_Dir{ dir } {}
		virtual ~MoveCommand() = default;

		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		void Execute() override;

	private:
		float m_Speed{};
		glm::vec2 m_Dir{};
	};
}

