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
	}
	else
	{
		if(m_Dir.x == 1.f && m_Dir.y == 0.f)
		{
			m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, -1.f, 0.f);
			m_Dir.x = -1.f;
			m_Dir.y = 0.f;
			m_IsValid = true;
		}
		else
		{
			m_pGameObject->GetComponent<MovementComponent>()->SetSpeed(200.f, 1.f, 0.f);
			m_Dir.x = 1.f;
			m_Dir.y = 0.f;
			m_IsValid = true;
		}
	}
}

void ValidCellComponent::SetGrid(GridComponent* pGrid)
{
	m_pGrid = pGrid;
}