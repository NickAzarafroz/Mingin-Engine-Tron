#include "SpawnBulletCommand.h"
#include "GridComponent.h"
#include "MovementComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "ValidCellComponent.h"
#include "BoxTriggerComponent.h"
#include "TextureComponent.h"
#include "ServiceLocator.h"
using namespace dae;

void SpawnBulletCommand::Execute()
{
	auto& scene = SceneManager::GetInstance().GetScene(1);
	auto& soundSystem = ServiceLocator::GetSoundSystem();

	if (scene.IsObjectInScene(m_GoBullet)) return;

	soundSystem.Play("../Data/Shoot.mp3", 20.f);

	m_GoBullet = std::make_shared<GameObject>(&scene);
	m_GoBullet->AddComponent<TextureComponent>()->AddTexture("BulletPlayer.png");
	m_GoBullet->AddComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x,
		GetGameActor()->GetLocalPosition().y,
		GetGameActor()->GetLocalPosition().z);

	m_GoBullet->AddComponent<ValidCellComponent>()->SetGrid(m_pGrid);
	m_GoBullet->GetComponent<ValidCellComponent>()->SetBounceThreshold(5);
	
	m_GoBullet->AddComponent<BoxTriggerComponent>()->SetSize(12.f, 12.f);

	for(const auto& object : m_pOtherGameObjects)
	{
		if(!object->IsDeleted())
		{
			object->GetComponent<BoxTriggerComponent>()->SetOtherObject(m_GoBullet.get());
			object->GetComponent<BoxTriggerComponent>()->SetPlayerObject(GetGameActor());
			object->GetComponent<BoxTriggerComponent>()->DestroyOtherAfterOverLap(true);
			object->GetComponent<BoxTriggerComponent>()->DecMyHealthAfterOverlap(true);
			object->GetComponent<BoxTriggerComponent>()->IncPlayerScoreAfterOverlap(true);
		}
	}

	//if (!m_pOtherGameObject->IsDeleted())
		//m_pOtherGameObject->GetComponent<BoxTriggerComponent>()->SetOtherObject(m_GoBullet.get());

	auto childActor = GetGameActor()->GetChildAtIndex(0);
	float angle = childActor->GetComponent<TextureComponent>()->GetAngle();

	if (angle == 0.f || angle == 360.f || angle == -360.f)
	{
		m_GoBullet->GetComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x + 33.f,
			GetGameActor()->GetLocalPosition().y + 8.f,
			GetGameActor()->GetLocalPosition().z);
		m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 1.f, 0.f);
		m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 1.f, 0.f });
	}
	else if (angle == 315.f || angle == -45.f)
	{
		m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, -0.5f);
		m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.5f, -0.5f });
	}
	else if (angle == 270.f || angle == -90.f)
	{
		m_GoBullet->GetComponent<TransformComponent>()->SetPosition(GetGameActor()->GetLocalPosition().x + 14.f,
			GetGameActor()->GetLocalPosition().y - 16.f,
			GetGameActor()->GetLocalPosition().z);
		m_GoBullet->AddComponent<MovementComponent>()->SetSpeed(200.f, 0.f, -1.f);
		m_GoBullet->GetComponent<ValidCellComponent>()->SetDirection(glm::vec2{ 0.f, -1.f });
	}
	else if (angle == 225.f || angle == -135.f)
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