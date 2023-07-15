#include "ValidCellComponent.h"
#include "GameObject.h"
#include "GridComponent.h"
#include "MovementComponent.h"
using namespace dae;

void ValidCellComponent::Update(float)
{
	if(m_IsValid)
	{
		m_IsValid = m_pGrid->GetDestinationCell(glm::vec2{ m_pGameObject->GetLocalPosition().x, m_pGameObject->GetLocalPosition().y }, m_Dir).second;
		if(m_IsValid)
		{
			m_HasCollided = false;
		}
	}
	else
	{
		if (m_AmountBounce >= 5)
		{
			m_pGameObject->RemoveGameObject();
		}

		if(!m_HasCollided)
		{
			m_HasCollided = true;

			if (m_Dir.x == 1.f && m_Dir.y == 0.f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -1.f, 0.f);
				m_Dir.x = -1.f;
				m_Dir.y = 0.f;
				m_AmountBounce++;
				m_IsValid = true;
			}
			else if (m_Dir.x == -1.f && m_Dir.y == 0.f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 1.f, 0.f);
				m_Dir.x = 1.f;
				m_Dir.y = 0.f;
				m_AmountBounce++;
				m_IsValid = true;
			}
			else if (m_Dir.x == 0.f && m_Dir.y == 1.f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.f, -1.f);
				m_Dir.x = 0.f;
				m_Dir.y = -1.f;
				m_AmountBounce++;
				m_IsValid = true;
			}
			else if (m_Dir.x == 0.f && m_Dir.y == -1.f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.f, 1.f);
				m_Dir.x = 0.f;
				m_Dir.y = 1.f;
				m_AmountBounce++;
				m_IsValid = true;
			}
			else if (m_Dir.x == 0.5f && m_Dir.y == 0.5f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, 0.5f);
				m_Dir.x = -0.5f;
				m_Dir.y = 0.5f;
				m_IsValid = true;
			}
			else if (m_Dir.x == 0.5f && m_Dir.y == -0.5f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, -0.5f);
				m_Dir.x = -0.5f;
				m_Dir.y = -0.5f;
				m_IsValid = true;
			}
			else if (m_Dir.x == -0.5f && m_Dir.y == -0.5f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, 0.5f);
				m_Dir.x = -0.5f;
				m_Dir.y = 0.5f;
				m_IsValid = true;
			}
			else if (m_Dir.x == -0.5f && m_Dir.y == 0.5f)
			{
				m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, 0.5f);
				m_Dir.x = 0.5f;
				m_Dir.y = 0.5f;
				m_IsValid = true;
			}
		}
	}
}

void ValidCellComponent::SetGrid(GridComponent* pGrid)
{
	m_pGrid = pGrid;
}

void ValidCellComponent::SetDirection(glm::vec2 dir)
{
	m_Dir = dir;
}

void ValidCellComponent::IncreaseBounce()
{
	++m_AmountBounce;
}

int ValidCellComponent::GetAmountBounce()
{
	return m_AmountBounce;
}
