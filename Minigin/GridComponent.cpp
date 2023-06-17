#include "GridComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"

#include "include/rapidjson/rapidjson.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/document.h"
#include <fstream>

using namespace dae;

void GridComponent::Start()
{
	m_pTexture = m_pGameObject->GetComponent<TextureComponent>();
}

void GridComponent::Render() const
{
	for (int i = 0; i < static_cast<int>(m_Cells.size()); i++)
	{
		switch (m_Cells[i].ID)
		{
		case 1:
			m_pTexture->SetActiveTexture(0);
			m_pTexture->SetPosition(m_Cells[i].localPosition.x, m_Cells[i].localPosition.y);
			m_pTexture->Render();
			break;
		case 2:
			m_pTexture->SetActiveTexture(1);
			m_pTexture->SetPosition(m_Cells[i].localPosition.x, m_Cells[i].localPosition.y);
			m_pTexture->Render();
			break;
		case 3:
			m_pTexture->SetActiveTexture(2);
			m_pTexture->SetPosition(m_Cells[i].localPosition.x, m_Cells[i].localPosition.y);
			m_pTexture->Render();
			break;
		case 4:
			m_pTexture->SetActiveTexture(3);
			m_pTexture->SetPosition(m_Cells[i].localPosition.x, m_Cells[i].localPosition.y);
			m_pTexture->Render();
			break;
		case 5:
			m_pTexture->SetActiveTexture(4);
			m_pTexture->SetPosition(m_Cells[i].localPosition.x, m_Cells[i].localPosition.y);
			m_pTexture->Render();
			break;
		case 6:
			m_pTexture->SetActiveTexture(5);
			m_pTexture->SetPosition(m_Cells[i].localPosition.x, m_Cells[i].localPosition.y);
			m_pTexture->Render();
			break;
		case 7:
			m_pTexture->SetActiveTexture(6);
			m_pTexture->SetPosition(m_Cells[i].localPosition.x, m_Cells[i].localPosition.y);
			m_pTexture->Render();
			break;
		default:
			break;
		}
	}
}

void dae::GridComponent::ReceiveMessage(int message)
{
	if(message == 0)
	{
		std::cout << "GridComponent: Message received\n";
	}
}

void GridComponent::Initialize(float cellWidth, float cellHeight, const std::string& filename)
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
			c.localPosition = glm::vec2{ col * cellWidth, row * cellHeight + 96.f};
			c.centerPosition = glm::vec2{ c.localPosition.x + cellWidth / 2, c.localPosition.y + cellHeight / 2};

			m_Cells.push_back(c);
		}
	}

	using rapidjson::Document;
	Document jsonDoc;

	std::fstream is{ filename };

	rapidjson::IStreamWrapper isw{ is };
	jsonDoc.ParseStream(isw);

	using rapidjson::Value;

	for (Value::ConstValueIterator itr = jsonDoc["data"].Begin(); itr != jsonDoc["data"].End(); ++itr)
	{
		const Value& textureID = *itr;

		m_TextureIDs.push_back(textureID.GetInt());
	}

	for (int i{}; i < static_cast<int>(m_TextureIDs.size()); ++i)
	{
		m_Cells[i].ID = m_TextureIDs[i];
	}
}

Cell GridComponent::GetCell(glm::vec2 localPosition) const
{
	int row = static_cast<int>((localPosition.y - 96.f) / m_CellHeight);
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
	int row = static_cast<int>((localPosition.y - 96.f) / m_CellHeight);
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
