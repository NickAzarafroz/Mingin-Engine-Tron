#pragma once
#include "GameActorCommand.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "MovementComponent.h"
#include "ValidCellComponent.h"
#include "SceneManager.h"
#include "Scene.h"
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
			if (!m_MovementFlag)
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

			if (m_TempDir.x == 1.f)																		// If the player is close enough snap him to the destination position and start again ...
			{
				GetGameActor()->GetComponent<TextureComponent>()->SetFlipped(false);
				GetGameActor()->GetComponent<TextureComponent>()->SetAngle(0.f);

				if (distanceX < 1.f)
				{
					x = m_DestinationCell.localPosition.x;
					m_MovementFlag = false;
				}
			}
			else if (m_TempDir.x == -1.f)
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

	class SpawnBulletCommand : public GameActorCommand
	{
	public:
		SpawnBulletCommand(GameObject* actor, GameObject* otherActor, GridComponent* pGrid) : GameActorCommand(actor), m_pOtherGameObject{otherActor}, m_pGrid { pGrid } {}
		virtual ~SpawnBulletCommand() = default;
		void Execute() override
		{
			auto& scene = SceneManager::GetInstance().GetScene(0);
			
			if (scene.IsObjectInScene(m_GoBullet)) return;

			m_GoBullet = std::make_shared<GameObject>(&scene);
			m_GoBullet->AddComponent<TextureComponent>()->AddTexture("BulletPlayer.png");
			m_GoBullet->AddComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x,
				GetGameActor()->GetLocalPosition().y,
				GetGameActor()->GetLocalPosition().z);

			m_GoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_GoBullet->AddComponent<BoxTriggerComponent>()->SetSize(12.f, 12.f);
			
			GetGameActor()->GetComponent<BoxTriggerComponent>()->SetOtherObject(m_GoBullet.get());

			if(!m_pOtherGameObject->IsDeleted())
			m_pOtherGameObject->GetComponent<BoxTriggerComponent>()->SetOtherObject(m_GoBullet.get());

			auto childActor = GetGameActor()->GetChildAtIndex(0);
			float angle = childActor->GetComponent<TextureComponent>()->GetAngle();

			if(angle == 0.f || angle == 360.f || angle == -360.f)
			{
				m_GoBullet->GetComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x + 33.f,
					GetGameActor()->GetLocalPosition().y + 8.f,
					GetGameActor()->GetLocalPosition().z);
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 1.f, 0.f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 1.f, 0.f });
			}
			else if(angle == 315.f || angle == -45.f)
			{
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, -0.5f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.5f, -0.5f });
			}
			else if(angle == 270.f || angle == -90.f)
			{
				m_GoBullet->GetComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x + 14.f,
					GetGameActor()->GetLocalPosition().y - 16.f,
					GetGameActor()->GetLocalPosition().z);
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 0.f, -1.f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, -1.f });
			}
			else if(angle == 225.f || angle == -135.f)
			{
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, -0.5f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ -0.5f, -0.5f });
			}
			else if (angle == 180.f || angle == -180.f)
			{
				m_GoBullet->GetComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x - 20.f,
					GetGameActor()->GetLocalPosition().y + 8.f,
					GetGameActor()->GetLocalPosition().z);
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, -1.0f, 0.f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ -1.f, 0.f });
			}
			else if (angle == 135.f || angle == -225.f)
			{
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, 0.5f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ -0.5f, 0.5f });
			}
			else if (angle == 90.f || angle == -270.f)
			{
				m_GoBullet->GetComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x + 14.f,
					GetGameActor()->GetLocalPosition().y + 40.f,
					GetGameActor()->GetLocalPosition().z);
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 0.f, 1.f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, 1.f });
			}
			else if (angle == 45.f || angle == -315.f)
			{
				m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, 0.5f);
				m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.5f, 0.5f });
			}
			
			m_GoBullet->AddGameObject();
			m_GoBullet->Start();

		}

	private:
		std::shared_ptr<GameObject> m_GoBullet{};
		GridComponent* m_pGrid{};
		GameObject* m_pOtherGameObject{};
	};

	class MoveTurretCommand : public GameActorCommand
	{
	public:
		MoveTurretCommand(GameObject* actor, bool increase) : GameActorCommand(actor), m_Increase{ increase } {}
		virtual ~MoveTurretCommand() = default;
		void Execute() override
		{
			if(m_Angle == 360.f || m_Angle == -360.f)
			{
				m_Angle = 0.f;
			}

			if (m_Increase)
			{
				m_Angle -= 45.f;
			}
			else
			{
				m_Angle += 45.f;
			}

			GetGameActor()->GetComponent<TextureComponent>()->SetAngle(m_Angle);
		}

		static float m_Angle;

	private:
		bool m_Increase{};
	};

	float MoveTurretCommand::m_Angle{};
}
