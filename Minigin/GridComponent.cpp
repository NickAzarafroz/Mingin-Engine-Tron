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
	m_CellWidth = cellWidth;
	m_CellHeight = cellHeight;

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

Cell GridComponent::GetCell(glm::vec2 localPosition) const
{
	int row = static_cast<int>(localPosition.x / m_CellWidth);
	int col = static_cast<int>(localPosition.y / m_CellHeight);

	if (row >= 0 && row < m_Rows && col >= 0 && col < m_Cols)
	{
		int index = row * m_Rows + col;
		return m_Cells[index];
	}
	else
	{
		return m_Cells[0];
	}

	// Return an invalid cell if the local position is not within any cell
	//...
}

Cell dae::GridComponent::GetDestinationCell(glm::vec2 localPosition, glm::vec2 dir)
{

}

GridComponent::~GridComponent()
{
}
