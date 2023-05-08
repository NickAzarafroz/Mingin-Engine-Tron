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
			float x = GetGameActor()->GetWorldPosition().x;
			float y = GetGameActor()->GetWorldPosition().y; 

			x += m_Dir.x * 50.f * GetGameActor()->GetElapsedSec();
			y += m_Dir.y * 50.f * GetGameActor()->GetElapsedSec();

			m_Cell = m_pGrid->GetCell(glm::vec2{ x,y });



			if(x < 0.f)
			{
				x = 8.f;
			}
			
			if(x > 448.f)
			{
				x = 424.f;
			}

			if(y < 0.f)
			{
				y = 8.f;
			}

			if(y > 576.f)
			{
				y = 552.f;
			}

			GetGameActor()->SetLocalPosition(glm::vec3(x, y, 0.0f));
		};

	private:
		glm::vec2 m_Dir{};
		GridComponent* m_pGrid{};
		Cell m_Cell{};
		Cell m_DestinationCell{};
	};
}
