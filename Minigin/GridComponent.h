#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"
#include <vector>
#include <string>
#include <memory>
namespace dae
{
	class TextureComponent;
	class GameObject;

	struct Cell
	{
		float height{};
		float width{};

		glm::vec2 centerPosition{};
		glm::vec2 localPosition{};

		int ID;
	};

	class GridComponent : public BaseComponent
	{
	public:
		GridComponent() = default;
		virtual void Start() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;

		void Initialize(float cellWidth, float cellHeight, const std::string& filename);
		Cell GetCell(glm::vec2 localPosition) const;
		std::pair<Cell, bool> GetDestinationCell(glm::vec2 localPosition, glm::vec2 dir);
		~GridComponent();

	private:
		const int m_Rows{ 18 };
		const int m_Cols{ 14 };

		float m_CellWidth;
		float m_CellHeight;

		TextureComponent* m_pTexture;
		std::vector<Cell> m_Cells;
		std::vector<int> m_TextureIDs;
	};
}