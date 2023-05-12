#pragma once
#include "GameActorCommand.h"
#include "PlayerComponent.h"
namespace dae
{
	class MoveCommand : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* actor, float speed, glm::vec2 dir) : GameActorCommand(actor), m_Speed{ speed }, m_Dir{ dir } {}
		virtual ~MoveCommand() = default;
		void Execute() override 
		{ 
			float x = GetGameActor()->GetWorldPosition().x;
			float y = GetGameActor()->GetWorldPosition().y;

			x += m_Speed * m_Dir.x * GetGameActor()->GetElapsedSec();
			y += m_Speed * m_Dir.y * GetGameActor()->GetElapsedSec();

			GetGameActor()->SetLocalPosition(glm::vec3(x, y, 0.0f));
		};

	private:
		float m_Speed{};
		glm::vec2 m_Dir{};
	};

	class MoveGridCommand : public GameActorCommand
	{
	public:
		MoveGridCommand(GameObject* actor, glm::vec2 dir, GridComponent* pGrid) : GameActorCommand(actor), m_Dir{ dir }, m_pGrid{ pGrid } {}
		virtual ~MoveGridCommand() = default;
		void Execute() override
		{
			float x = GetGameActor()->GetWorldPosition().x;
			float y = GetGameActor()->GetWorldPosition().y;

			if(!m_MovementFlag)
			{
				m_TempDir = m_Dir;
				m_Cell = m_pGrid->GetCell(glm::vec2{ x,y });
				m_DestinationCell = m_pGrid->GetDestinationCell(glm::vec2{ x,y }, m_TempDir);
				m_MovementFlag = true;
			}

			x += m_TempDir.x * 50.f * GetGameActor()->GetElapsedSec();
			y += m_TempDir.y * 50.f * GetGameActor()->GetElapsedSec();

			float distanceX = fabs(m_DestinationCell.centerPosition.x - (x + m_Cell.width / 2));
			float distanceY = fabs(m_DestinationCell.centerPosition.y - (y + m_Cell.height / 2));

			if(m_TempDir.x == 1.f)
			{
				if(distanceX < 1.f)
				{
					x = m_DestinationCell.localPosition.x;
					m_MovementFlag = false;
				}
			}
			else if(m_TempDir.x == -1.f)
			{
				if (distanceX < 1.f)
				{
					x = m_DestinationCell.localPosition.x;
					m_MovementFlag = false;
				}
			}

			if (m_TempDir.y == 1.f)
			{
				if (distanceY < 1.f)
				{
					y = m_DestinationCell.localPosition.y;
					m_MovementFlag = false;
				}
			}
			else if (m_TempDir.y == -1.f)
			{
				if (distanceY < 1.f)
				{
					y = m_DestinationCell.localPosition.y;
					m_MovementFlag = false;
				}
			}

			GetGameActor()->SetLocalPosition(glm::vec3(x, y, 0.0f));
			
		};

		static bool m_MovementFlag;
		static glm::vec2 m_TempDir;
		static Cell m_Cell;
		static Cell m_DestinationCell;

	private:
		glm::vec2 m_Dir{};
		GridComponent* m_pGrid{};
	};

	bool MoveGridCommand::m_MovementFlag{};
	glm::vec2 MoveGridCommand::m_TempDir{};
	Cell MoveGridCommand::m_Cell{};
	Cell MoveGridCommand::m_DestinationCell{};

	class ChangeHealthCommand : public GameActorCommand
	{
	public:
		ChangeHealthCommand(GameObject* actor, int amount) : GameActorCommand(actor), m_Amount{ amount } {}
		virtual ~ChangeHealthCommand() = default;
		void Execute() override
		{
			GetGameActor()->GetComponent<PlayerComponent>()->TakeDamage(m_Amount);
		}

	private:
		int m_Amount;
	};
}
