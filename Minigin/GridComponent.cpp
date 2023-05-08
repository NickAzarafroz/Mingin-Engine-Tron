#include "GridComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
using namespace dae;

void GridComponent::Start()
{
	m_pTexture = m_pGameObject->GetComponent<TextureComponent>();
}

void GridComponent::Update(float)
{
}

void GridComponent::Render() const
{
	for (int col{0}; col < m_Cols; ++col)
	{
		for (int row{0}; row < m_Rows; ++row)
		{
			m_pTexture->SetPosition(static_cast<float>(row * 32), static_cast<float>(col * 32));
			m_pTexture->Render();
		}
	}
}

void GridComponent::Initialize(float cellWidth, float cellHeight)
{
	for (int col{ 0 }; col < m_Cols; ++col)
	{
		for (int row{ 0 }; row < m_Rows; ++row)
		{
			Cell c;
			c.width = cellWidth;
			c.height = cellHeight;
			c.localPosition = glm::vec2{ row * cellWidth, col * cellHeight };
			c.centerPosition = glm::vec2{ (c.localPosition.x + cellWidth) / 2, (c.localPosition.y + cellHeight) / 2 };
			m_Cells.push_back(c);
		}
	}
}

dae::GridComponent::~GridComponent()
{
}
