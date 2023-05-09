#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class MoveCommand : public GameActorCommand
	{
	public:
		MoveCommand(GameObject* actor, float speed, glm::vec2 dir) : GameActorCommand(actor), m_Speed{ speed }, m_Dir{ dir } {}
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
		void Execute() override
		{
			if(!m_DestinationReached)
			{
				float x = GetGameActor()->GetWorldPosition().x;
				float y = GetGameActor()->GetWorldPosition().y;

				if(m_DoUntilFinished)
				{
					m_Cell = m_pGrid->GetCell(glm::vec2{ x,y });
					m_DestinationCell = m_pGrid->GetDestinationCell(glm::vec2{ x,y }, m_Dir);
					m_DoUntilFinished = false;
				}

				if (fabs((x * 2.f) - m_DestinationCell.centerPosition.x) < 0.1f && fabs((y * 2.f) - m_DestinationCell.centerPosition.y) < 0.1f)
				{
					m_DestinationReached = true;
				}

				glm::vec2 distance = m_DestinationCell.centerPosition - m_Cell.centerPosition;

				float length = static_cast<float>(distance.length());
				distance.x /= length;
				distance.y /= length;

				x += distance.x * 10.f * GetGameActor()->GetElapsedSec();
				y += distance.y * 10.f * GetGameActor()->GetElapsedSec();

				GetGameActor()->SetLocalPosition(glm::vec3(x, y, 0.0f));
			}
		};

	private:
		glm::vec2 m_Dir{};
		GridComponent* m_pGrid{};
		Cell m_Cell{};
		Cell m_DestinationCell{};
		bool m_DestinationReached{};
		bool m_DoUntilFinished{ true };
	};
}
