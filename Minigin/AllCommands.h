#pragma once
#include "GameActorCommand.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
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
			// Get the position of the player
			float x = GetGameActor()->GetWorldPosition().x;
			float y = GetGameActor()->GetWorldPosition().y;

			// Player reached his destination so check if we can go to the next one
			if(!m_MovementFlag)
			{
				m_TempDir = m_Dir;																		// Save direction in temp because we should only remember the direction in the beginning
				m_Cell = m_pGrid->GetCell(glm::vec2{ x,y });											
				m_DestinationCell = m_pGrid->GetDestinationCell(glm::vec2{ x,y }, m_TempDir).first;
				m_IsValid = m_pGrid->GetDestinationCell(glm::vec2{ x,y }, m_TempDir).second;			// Only move if the destination cell is valid
				if (!m_IsValid) return;
				m_MovementFlag = true;
			}

			x += m_TempDir.x * 50.f * GetGameActor()->GetElapsedSec();									// Move to destination with certain amount of speed TODO: fix magic numbers :)
			y += m_TempDir.y * 50.f * GetGameActor()->GetElapsedSec();

			float distanceX = fabs(m_DestinationCell.centerPosition.x - (x + m_Cell.width / 2));		// Calculate the distance from the destionation and the player (length)
			float distanceY = fabs(m_DestinationCell.centerPosition.y - (y + m_Cell.height / 2));

			if(m_TempDir.x == 1.f)																		// If the player is close enough snap him to the destination position and start again ...
			{
				GetGameActor()->GetComponent<TextureComponent>()->SetFlipped(false);
				GetGameActor()->GetComponent<TextureComponent>()->SetAngle(0.f);

				if(distanceX < 1.f)
				{
					x = m_DestinationCell.localPosition.x;
					m_MovementFlag = false;
				}
			}
			else if(m_TempDir.x == -1.f)
			{
				GetGameActor()->GetComponent<TextureComponent>()->SetFlipped(true);
				GetGameActor()->GetComponent<TextureComponent>()->SetAngle(0.f);

				if (distanceX < 1.f)
				{
					x = m_DestinationCell.localPosition.x;
					m_MovementFlag = false;
				}
			}

			if (m_TempDir.y == 1.f)
			{
				if (m_TempDir.x == -1.f) 
				{
					GetGameActor()->GetComponent<TextureComponent>()->SetFlipped(true);
				}
				else
				{
					GetGameActor()->GetComponent<TextureComponent>()->SetAngle(90.f);
					GetGameActor()->GetComponent<TextureComponent>()->SetFlipped(false);
				}

				if (distanceY < 1.f)
				{
					y = m_DestinationCell.localPosition.y;
					m_MovementFlag = false;
				}
			}
			else if (m_TempDir.y == -1.f)
			{
				if (m_TempDir.x == -1.f) 
				{
					GetGameActor()->GetComponent<TextureComponent>()->SetFlipped(true);
				}
				else
				{
					GetGameActor()->GetComponent<TextureComponent>()->SetAngle(-90.f);
					GetGameActor()->GetComponent<TextureComponent>()->SetFlipped(false);
				}

				if (distanceY < 1.f)
				{
					y = m_DestinationCell.localPosition.y;
					m_MovementFlag = false;
				}
			}

			GetGameActor()->SetLocalPosition(glm::vec3(x, y, 0.0f));
			
		};

		static bool m_MovementFlag;
		static bool m_IsValid;
		static glm::vec2 m_TempDir;
		static Cell m_Cell;
		static Cell m_DestinationCell;

	private:
		glm::vec2 m_Dir{};
		GridComponent* m_pGrid{};
	};

	bool MoveGridCommand::m_MovementFlag{};
	bool MoveGridCommand::m_IsValid{};
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
