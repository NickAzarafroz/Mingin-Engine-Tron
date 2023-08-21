#include "AIComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "MovementComponent.h"
#include "ValidCellComponent.h"
#include "BoxTriggerComponent.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void AIComponent::Update(float)
{
	Wander();

	if(!m_pPlayers.empty()) ShootPlayer();
}

void AIComponent::AddObjectToShoot(std::shared_ptr<GameObject> pPlayer)
{
	m_pPlayers.emplace_back(pPlayer);
}

void AIComponent::SetGrid(GridComponent* pGrid)
{
	m_pGrid = pGrid;
}

void AIComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

void AIComponent::SetMovementFlag(bool flag)
{
	m_MovementFlag = flag;
}

void AIComponent::Wander()
{
	m_Dir.x = static_cast<float>(rand() % 3 - 1);
	m_Dir.y = static_cast<float>(rand() % 3 - 1);

	if (m_Dir.x == 1.f || m_Dir.x == -1.f)
	{
		m_Dir.y = 0.f;
	}
	else
	{
		do
		{
			m_Dir.y = static_cast<float>(rand() % 3 - 1);
		} while (m_Dir.y == 0.f);
	}

	// Get the position of the player
	float x = m_pGameObject->GetWorldPosition().x;
	float y = m_pGameObject->GetWorldPosition().y;

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

	x += m_TempDir.x * m_Speed * m_pGameObject->GetElapsedSec();									// Move to destination with certain amount of speed TODO: fix magic numbers :)
	y += m_TempDir.y * m_Speed * m_pGameObject->GetElapsedSec();

	float distanceX = fabs(m_DestinationCell.centerPosition.x - (x + m_Cell.width / 2));		// Calculate the distance from the destionation and the player (length)
	float distanceY = fabs(m_DestinationCell.centerPosition.y - (y + m_Cell.height / 2));

	if (m_TempDir.x == 1.f)																		// If the player is close enough snap him to the destination position and start again ...
	{
		m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(false);
		m_pGameObject->GetComponent<TextureComponent>()->SetAngle(0.f);

		if (distanceX < 1.f)
		{
			x = m_DestinationCell.localPosition.x;
			m_MovementFlag = false;
		}
	}
	else if (m_TempDir.x == -1.f)
	{
		m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(true);
		m_pGameObject->GetComponent<TextureComponent>()->SetAngle(0.f);

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
			m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(true);
		}
		else
		{
			m_pGameObject->GetComponent<TextureComponent>()->SetAngle(90.f);
			m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(false);
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
			m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(true);
		}
		else
		{
			m_pGameObject->GetComponent<TextureComponent>()->SetAngle(-90.f);
			m_pGameObject->GetComponent<TextureComponent>()->SetFlipped(false);
		}

		if (distanceY < 1.f)
		{
			y = m_DestinationCell.localPosition.y;
			m_MovementFlag = false;
		}
	}

	m_pGameObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

}

void AIComponent::ShootPlayer()
{
	auto& scene = SceneManager::GetInstance().GetScene(1);

	if (!scene.IsObjectInScene(m_pPlayers[0])) return;

	// Get the position of the enemy
	float x = m_pGameObject->GetWorldPosition().x;
	float y = m_pGameObject->GetWorldPosition().y;

	// Get the position of the player
	float px = m_pPlayers[0]->GetWorldPosition().x;
	float py = m_pPlayers[0]->GetWorldPosition().y;

	float p2x{};
	float p2y{};

	if(m_pPlayers.size() > 1)
	{
		p2x = m_pPlayers[1]->GetWorldPosition().x;
		p2y = m_pPlayers[1]->GetWorldPosition().y;
	}

	if(m_pGrid->GetCell(glm::vec2{x,y}).row == m_pGrid->GetCell(glm::vec2{px, py}).row)
	{
		if (scene.IsObjectInScene(m_pGoBullet)) return;

		m_pGoBullet = std::make_shared<GameObject>(&scene);
		m_pGoBullet->AddComponent<TextureComponent>()->AddTexture("BulletNPC.png");
		m_pGoBullet->AddComponent<TransformComponent>()->SetPosition(m_pGameObject->GetWorldPosition().x + 12.f, m_pGameObject->GetWorldPosition().y + 10.f, 0);
		m_pGoBullet->AddComponent<BoxTriggerComponent>()->SetSize(12.f, 12.f);
		m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[0]);
		if(m_pPlayers.size() > 1) m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[1]);
		m_pGoBullet->GetComponent<BoxTriggerComponent>()->DecOtherHealthAfterOverlap(true);

		if(m_pGrid->GetCell(glm::vec2{x,y}).col > m_pGrid->GetCell(glm::vec2{ px, py }).col)
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, -1.f, 0.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ -1.f, 0.f });
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetBounceThreshold(0);
		}
		else
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, 1.f, 0.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 1.f, 0.f });
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetBounceThreshold(0);
		}

		m_pGoBullet->AddGameObject();
		m_pGoBullet->Start();
	}
	else if (m_pGrid->GetCell(glm::vec2{ x,y }).col == m_pGrid->GetCell(glm::vec2{ px, py }).col)
	{
		if (scene.IsObjectInScene(m_pGoBullet)) return;

		m_pGoBullet = std::make_shared<GameObject>(&scene);
		m_pGoBullet->AddComponent<TextureComponent>()->AddTexture("BulletNPC.png");
		m_pGoBullet->AddComponent<TransformComponent>()->SetPosition(m_pGameObject->GetWorldPosition().x + 12.f, m_pGameObject->GetWorldPosition().y + 10.f, 0);
		m_pGoBullet->AddComponent<BoxTriggerComponent>()->SetSize(12.f, 12.f);
		m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[0]);
		if (m_pPlayers.size() > 1) m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[1]);
		m_pGoBullet->GetComponent<BoxTriggerComponent>()->DecOtherHealthAfterOverlap(true);

		if (m_pGrid->GetCell(glm::vec2{ x,y }).row > m_pGrid->GetCell(glm::vec2{ px, py }).row)
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, 0.f, -1.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, -1.f });
		}
		else
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, 0.f, 1.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, 1.f });
		}

		m_pGoBullet->AddGameObject();
		m_pGoBullet->Start();
	}

	if(m_pPlayers.size() > 1)
	{
		if (m_pGrid->GetCell(glm::vec2{ x,y }).row == m_pGrid->GetCell(glm::vec2{ p2x, p2y }).row)
		{
			if (scene.IsObjectInScene(m_pGoBullet)) return;

			m_pGoBullet = std::make_shared<GameObject>(&scene);
			m_pGoBullet->AddComponent<TextureComponent>()->AddTexture("BulletNPC.png");
			m_pGoBullet->AddComponent<TransformComponent>()->SetPosition(m_pGameObject->GetWorldPosition().x + 12.f, m_pGameObject->GetWorldPosition().y + 10.f, 0);
			m_pGoBullet->AddComponent<BoxTriggerComponent>()->SetSize(12.f, 12.f);
			m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[0]);
			m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[1]);
			m_pGoBullet->GetComponent<BoxTriggerComponent>()->DecOtherHealthAfterOverlap(true);

			if (m_pGrid->GetCell(glm::vec2{ x,y }).col > m_pGrid->GetCell(glm::vec2{ p2x, p2y }).col)
			{
				m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, -1.f, 0.f);
				m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
				m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ -1.f, 0.f });
				m_pGoBullet->GetComponent<ValidCellComponent>()->SetBounceThreshold(0);
			}
			else
			{
				m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, 1.f, 0.f);
				m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
				m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 1.f, 0.f });
				m_pGoBullet->GetComponent<ValidCellComponent>()->SetBounceThreshold(0);
			}

			m_pGoBullet->AddGameObject();
			m_pGoBullet->Start();
		}
		else if (m_pGrid->GetCell(glm::vec2{ x,y }).col == m_pGrid->GetCell(glm::vec2{ p2x, p2y }).col)
		{
			if (scene.IsObjectInScene(m_pGoBullet)) return;

			m_pGoBullet = std::make_shared<GameObject>(&scene);
			m_pGoBullet->AddComponent<TextureComponent>()->AddTexture("BulletNPC.png");
			m_pGoBullet->AddComponent<TransformComponent>()->SetPosition(m_pGameObject->GetWorldPosition().x + 12.f, m_pGameObject->GetWorldPosition().y + 10.f, 0);
			m_pGoBullet->AddComponent<BoxTriggerComponent>()->SetSize(12.f, 12.f);
			m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[0]);
			if (m_pPlayers.size() > 1) m_pGoBullet->GetComponent<BoxTriggerComponent>()->AddOtherObject(m_pPlayers[1]);
			m_pGoBullet->GetComponent<BoxTriggerComponent>()->DecOtherHealthAfterOverlap(true);

			if (m_pGrid->GetCell(glm::vec2{ x,y }).row > m_pGrid->GetCell(glm::vec2{ p2x, p2y }).row)
			{
				m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, 0.f, -1.f);
				m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
				m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, -1.f });
			}
			else
			{
				m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(150.f, 0.f, 1.f);
				m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
				m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, 1.f });
			}

			m_pGoBullet->AddGameObject();
			m_pGoBullet->Start();
		}
	}
}