#include "AIComponent.h"
#include "GridComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "MovementComponent.h"
#include "ValidCellComponent.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

bool AIComponent::m_MovementFlag{};
bool AIComponent::m_IsValid{};
glm::vec2 AIComponent::m_TempDir{};
Cell AIComponent::m_Cell{};
Cell AIComponent::m_DestinationCell{};

void AIComponent::Update(float)
{
	//MoveToObject();
	ShootPlayer();
}

void AIComponent::SetObjectToMoveTo(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
}

void AIComponent::SetGrid(GridComponent* pGrid)
{
	m_pGrid = pGrid;
}

void AIComponent::MoveToObject()
{
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

	x += m_TempDir.x * 50.f * m_pGameObject->GetElapsedSec();									// Move to destination with certain amount of speed TODO: fix magic numbers :)
	y += m_TempDir.y * 50.f * m_pGameObject->GetElapsedSec();

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
	// Get the position of the enemy
	float x = m_pGameObject->GetWorldPosition().x;
	float y = m_pGameObject->GetWorldPosition().y;

	// Get the position of the player
	float px = m_pPlayer->GetWorldPosition().x;
	float py = m_pPlayer->GetWorldPosition().y;

	if(m_pGrid->GetCell(glm::vec2{x,y}).row == m_pGrid->GetCell(glm::vec2{px, py}).row)
	{
		auto& scene = SceneManager::GetInstance().GetScene(0);

		if (scene.IsObjectInScene(m_pGoBullet)) return;

		m_pGoBullet = std::make_shared<GameObject>(&scene);
		m_pGoBullet->AddComponent<TextureComponent>()->AddTexture("BulletNPC.png");
		m_pGoBullet->AddComponent<TransformComponent>()->SetPosition(m_pGameObject->GetWorldPosition().x + 12.f, m_pGameObject->GetWorldPosition().y + 10.f, 0);

		if(m_pGrid->GetCell(glm::vec2{x,y}).col > m_pGrid->GetCell(glm::vec2{ px, py }).col)
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(300.f, -1.f, 0.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ -1.f, 0.f });
		}
		else
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(300.f, 1.f, 0.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 1.f, 0.f });
		}

		m_pGoBullet->AddGameObject();
		m_pGoBullet->Start();
	}
	else if(m_pGrid->GetCell(glm::vec2{ x,y }).col == m_pGrid->GetCell(glm::vec2{ px, py }).col)
	{
		auto& scene = SceneManager::GetInstance().GetScene(0);

		if (scene.IsObjectInScene(m_pGoBullet)) return;

		m_pGoBullet = std::make_shared<GameObject>(&scene);
		m_pGoBullet->AddComponent<TextureComponent>()->AddTexture("BulletNPC.png");
		m_pGoBullet->AddComponent<TransformComponent>()->SetPosition(m_pGameObject->GetWorldPosition().x + 12.f, m_pGameObject->GetWorldPosition().y + 10.f, 0);

		if (m_pGrid->GetCell(glm::vec2{ x,y }).row > m_pGrid->GetCell(glm::vec2{ px, py }).row)
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(300.f, 0.f, -1.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, -1.f });
		}
		else
		{
			m_pGoBullet->AddComponent<MovementComponent>()->SetSpeed(300.f, 0.f, 1.f);
			m_pGoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
			m_pGoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, 1.f });
		}

		m_pGoBullet->AddGameObject();
		m_pGoBullet->Start();
	}
}