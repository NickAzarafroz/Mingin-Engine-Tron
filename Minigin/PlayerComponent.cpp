#include "PlayerComponent.h"
#include "GameObject.h"
#include <iostream>
using namespace dae;

void PlayerComponent::Start()
{
	m_Health = 3;
}

void PlayerComponent::Update(float)
{
	if(m_Health <= 0)
	{
		Destroy();
	}
}

void PlayerComponent::ReceiveMessage(int message)
{
	if(message == 0)
	{
		std::cout << "PlayerComponent: Received Message\n";
	}
}

int PlayerComponent::GetHealth() const
{
	return m_Health;
}

void PlayerComponent::TakeDamage(int amount)
{
	m_Health -= amount;

	healthChanged.Notify();
}

void PlayerComponent::Destroy()
{
	m_pGameObject->MarkForDelete();
}

PlayerComponent::~PlayerComponent()
{
}
