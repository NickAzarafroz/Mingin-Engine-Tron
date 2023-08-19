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

		static bool m_MovementFlag;

	private:
		glm::vec2 m_Dir{};
		GridComponent* m_pGrid{};

		static bool m_IsValid;
		static glm::vec2 m_TempDir;
		static Cell m_Cell;
		static Cell m_DestinationCell;
	};

	class MoveGridCommandP2 : public GameActorCommand
	{
	public:
		MoveGridCommandP2(GameObject* actor, glm::vec2 dir, GridComponent* pGrid) : GameActorCommand(actor), m_Dir{ dir }, m_pGrid{ pGrid } {}
		virtual ~MoveGridCommandP2() = default;

		MoveGridCommandP2(const MoveGridCommandP2& other) = delete;
		MoveGridCommandP2(MoveGridCommandP2&& other) = delete;
		MoveGridCommandP2& operator=(const MoveGridCommandP2& other) = delete;
		MoveGridCommandP2& operator=(MoveGridCommandP2&& other) = delete;

		void Execute() override;

		static bool m_MovementFlag;

	private:
		glm::vec2 m_Dir{};
		GridComponent* m_pGrid{};

		static bool m_IsValid;
		static glm::vec2 m_TempDir;
		static Cell m_Cell;
		static Cell m_DestinationCell;
	};
}

