#include "PlayerComponent.h"
using namespace dae;

void PlayerComponent::Start()
{
	m_Health = 3;
}

void PlayerComponent::Update(float)
{
}

void PlayerComponent::Render() const
{
}

int dae::PlayerComponent::GetHealth() const
{
	return m_Health;
}

void dae::PlayerComponent::TakeDamage(int amount)
{
	m_Health -= amount;

	healthChanged.Notify();
}

PlayerComponent::~PlayerComponent()
{
}
