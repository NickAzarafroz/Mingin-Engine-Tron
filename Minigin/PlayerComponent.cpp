#include "PlayerComponent.h"
using namespace dae;

void PlayerComponent::Start()
{
}

void PlayerComponent::Update(float elapsedSec)
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
