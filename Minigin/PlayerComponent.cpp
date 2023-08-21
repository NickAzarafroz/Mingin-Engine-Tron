#include "PlayerComponent.h"
#include "GameObject.h"
#include <iostream>
using namespace dae;

void PlayerComponent::Start()
{
	m_Health = 3;
	if (m_Name.empty()) m_Name = "NoName";
}

void PlayerComponent::Update(float)
{
	if(m_Health < 0)
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

int PlayerComponent::GetScore() const
{
	return m_Score;
}

std::string dae::PlayerComponent::GetName() const
{
	return m_Name;
}

void PlayerComponent::TakeDamage(int amount)
{
	m_Health -= amount;

	healthChanged.Notify();
}

void PlayerComponent::IncreaseScore(int amount)
{
	m_Score += amount;

	scoreChanged.Notify();
}

void PlayerComponent::Destroy()
{
	m_pGameObject->MarkForDelete();
}

void PlayerComponent::SetName(std::string name)
{
	m_Name = name;
}

PlayerComponent::~PlayerComponent()
{
}
