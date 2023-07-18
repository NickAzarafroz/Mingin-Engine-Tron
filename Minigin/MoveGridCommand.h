#pragma once
#include "GameActorCommand.h"
namespace dae 
{
	struct Cell;
	class GridComponent;
	class MoveGridCommand : public GameActorCommand
	{
	public:
		MoveGridCommand(GameObject* actor, glm::vec2 dir, GridComponent* pGrid) : GameActorCommand(actor), m_Dir{ dir }, m_pGrid{ pGrid } {}
		virtual ~MoveGridCommand() = default;

		MoveGridCommand(const MoveGridCommand& other) = delete;
		MoveGridCommand(MoveGridCommand&& other) = delete;
		MoveGridCommand& operator=(const MoveGridCommand& other) = delete;
		MoveGridCommand& operator=(MoveGridCommand&& other) = delete;

		void Execute() override;

	private:
		glm::vec2 m_Dir{};
		GridComponent* m_pGrid{};

		static bool m_MovementFlag;
		static bool m_IsValid;
		static glm::vec2 m_TempDir;
		static Cell m_Cell;
		static Cell m_DestinationCell;
	};
}
