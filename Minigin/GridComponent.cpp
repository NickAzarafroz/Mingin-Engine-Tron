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
	for (int row{0}; row < m_Rows; ++row)
	{
		for (int col{0}; col < m_Cols; ++col)
		{
			m_pTexture->SetPosition(static_cast<float>(col * 32), static_cast<float>(row * 32));
			m_pTexture->Render();
		}
	}
}

void GridComponent::Initialize(float cellWidth, float cellHeight)
{
	m_CellWidth = cellWidth;
	m_CellHeight = cellHeight;

	for (int row{ 0 }; row < m_Rows; ++row)
	{
		for (int col{ 0 }; col < m_Cols; ++col)
		{
			Cell c;
			c.width = cellWidth;
			c.height = cellHeight;
			c.localPosition = glm::vec2{ col * cellWidth, row * cellHeight };
			c.centerPosition = glm::vec2{ c.localPosition.x + cellWidth / 2, c.localPosition.y + cellHeight / 2 };
			m_Cells.push_back(c);
		}
	}
}

Cell GridComponent::GetCell(glm::vec2 localPosition) const
{
	int row = static_cast<int>(localPosition.y / m_CellHeight);
	int col = static_cast<int>(localPosition.x / m_CellWidth);

	if (row >= 0 && row < m_Rows && col >= 0 && col < m_Cols)
	{
		int index = row * m_Cols + col;
		return m_Cells[index];
	}

	std::cout << "OutOfRange";
	return m_Cells[0];
}

std::pair<Cell, bool> dae::GridComponent::GetDestinationCell(glm::vec2 localPosition, glm::vec2 dir)
{
	int row = static_cast<int>(localPosition.y / m_CellHeight);
	int col = static_cast<int>(localPosition.x / m_CellWidth);

	int newRow = row + static_cast<int>(dir.y);
	int newCol = col + static_cast<int>(dir.x);

	if (newRow >= 0 && newRow < m_Rows && newCol >= 0 && newCol < m_Cols)
	{
		int index = newRow * m_Cols + newCol;
		return std::make_pair(m_Cells[index], true);
	}
	else
	{
		std::cout << "IsgoingTobeoutofrange";
		return std::make_pair(Cell{}, false);
	}
}

GridComponent::~GridComponent()
{
}
