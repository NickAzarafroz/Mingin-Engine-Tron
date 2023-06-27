#include "MovementComponent.h"
#include "GameObject.h"
using namespace dae;

void MovementComponent::Start()
{
	m_PosX = m_pGameObject->GetWorldPosition().x;
	m_PosY = m_pGameObject->GetWorldPosition().y;
}

void MovementComponent::Update(float elapsedSec)
{
	m_PosX += m_DirX * m_Speed * elapsedSec;
	m_PosY += m_DirY * m_Speed * elapsedSec;

	m_pGameObject->SetLocalPosition(glm::vec3(m_PosX, m_PosY, 0.0f));
}

void MovementComponent::SetSpeed(float speed, float x, float y)
{
	m_Speed = speed;
	m_DirX = x;
	m_DirY = y;
}
