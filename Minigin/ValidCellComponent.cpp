#include "ValidCellComponent.h"
#include "GameObject.h"
#include "MovementComponent.h"
using namespace dae;

void ValidCellComponent::Update(float)
{
	m_CellID = m_pGrid->GetCell(m_pGameObject->GetWorldPosition()).ID;

	if(m_CellID < 1)
	{
		m_BulletTrail.emplace_back(m_pGrid->GetCell(m_pGameObject->GetWorldPosition()));
	}
	else
	{
		if(m_pGameObject->GetWorldPosition().x < 0.f || m_pGameObject->GetWorldPosition().x > 640.f || 
 			m_pGameObject->GetWorldPosition().y < 96.f || m_pGameObject->GetWorldPosition().y > 580.f)
		{
			m_pGameObject->RemoveGameObject();
		}

		if (m_AmountBounce >= m_BounceThreshold)
		{
			m_pGameObject->RemoveGameObject();
		}

		if (m_Dir.x == 1.f && m_Dir.y == 0.f)
		{
			m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -1.f, 0.f);
			m_Dir.x = -1.f;
			m_Dir.y = 0.f;
			m_AmountBounce++;
			m_BulletTrail.clear();
		}
		else if (m_Dir.x == -1.f && m_Dir.y == 0.f)
		{
			m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 1.f, 0.f);
			m_Dir.x = 1.f;
			m_Dir.y = 0.f;
			m_AmountBounce++;
			m_BulletTrail.clear();
		}
		else if (m_Dir.x == 0.f && m_Dir.y == 1.f)
		{
			m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.f, -1.f);
			m_Dir.x = 0.f;
			m_Dir.y = -1.f;
			m_AmountBounce++;
			m_BulletTrail.clear();
		}
		else if (m_Dir.x == 0.f && m_Dir.y == -1.f)
		{
			m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.f, 1.f);
			m_Dir.x = 0.f;
			m_Dir.y = 1.f;
			m_AmountBounce++;
			m_BulletTrail.clear();
		}
		else if (m_Dir.x == 0.5f && m_Dir.y == 0.5f)
		{
			if(!m_BulletTrail.empty())
			{
				m_CurrentCell = m_pGrid->GetCell(m_pGameObject->GetWorldPosition());

				if (m_BulletTrail.back().row == m_CurrentCell.row)
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, 0.5f);
					m_Dir.x = -0.5f;
					m_Dir.y = 0.5f;
					m_AmountBounce++;
				}
				else
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, -0.5f);
					m_Dir.x = 0.5f;
					m_Dir.y = -0.5f;
					m_AmountBounce++;
				}

				m_BulletTrail.clear();
			}
		}
		else if (m_Dir.x == 0.5f && m_Dir.y == -0.5f)
		{
			if(!m_BulletTrail.empty())
			{
				m_CurrentCell = m_pGrid->GetCell(m_pGameObject->GetWorldPosition());

				if (m_BulletTrail.back().row == m_CurrentCell.row)
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, -0.5f);
					m_Dir.x = -0.5f;
					m_Dir.y = -0.5f;
					m_AmountBounce++;
				}
				else
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, 0.5f);
					m_Dir.x = 0.5f;
					m_Dir.y = 0.5f;
					m_AmountBounce++;
				}

				m_BulletTrail.clear();
			}
		}
		else if (m_Dir.x == -0.5f && m_Dir.y == -0.5f)
		{
			if(!m_BulletTrail.empty())
			{
				m_CurrentCell = m_pGrid->GetCell(m_pGameObject->GetWorldPosition());

				if (m_BulletTrail.back().row == m_CurrentCell.row)
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, -0.5f);
					m_Dir.x = 0.5f;
					m_Dir.y = -0.5f;
					m_AmountBounce++;
				}
				else
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, 0.5f);
					m_Dir.x = -0.5f;
					m_Dir.y = 0.5f;
					m_AmountBounce++;
				}
			}

			m_BulletTrail.clear();
		}
		else if (m_Dir.x == -0.5f && m_Dir.y == 0.5f)
		{
			if(!m_BulletTrail.empty())
			{
				m_CurrentCell = m_pGrid->GetCell(m_pGameObject->GetWorldPosition());

				if (m_BulletTrail.back().row == m_CurrentCell.row)
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 0.5f, 0.5f);
					m_Dir.x = 0.5f;
					m_Dir.y = 0.5f;
					m_AmountBounce++;
				}
				else
				{
					m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -0.5f, -0.5f);
					m_Dir.x = -0.5f;
					m_Dir.y = -0.5f;
					m_AmountBounce++;
				}

				m_BulletTrail.clear();
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

void ValidCellComponent::SetBounceThreshold(int amount)
{
	m_BounceThreshold = amount;
}

int ValidCellComponent::GetAmountBounce()
{
	return m_AmountBounce;
}
