#include "EnemyComponent.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include <iostream>
using namespace dae;

void EnemyComponent::Start()
{
	m_Health = 3;
}

void EnemyComponent::Update(float)
{
	if (m_Health <= 0)
	{
		Destroy();
	}
}

void EnemyComponent::ReceiveMessage(int message)
{
	if (message == 0)
	{
		std::cout << "PlayerComponent: Received Message\n";
	}
}

void EnemyComponent::SetPlayer(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
}

int EnemyComponent::GetHealth() const
{
	return m_Health;
}

void EnemyComponent::TakeDamage(int amount)
{
	m_Health -= amount;
}

void EnemyComponent::Destroy()
{
	m_pPlayer->GetComponent<PlayerComponent>()->IncreaseScore(100);
	m_pGameObject->MarkForDelete();
}