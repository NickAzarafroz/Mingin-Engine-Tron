#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"
#include <vector>
namespace dae
{
	struct Cell
	{
		float height;
		float width;
		glm::vec2 centerPosition{};
		glm::vec2 localPosition{};
	};

	class TextureComponent;
	class GameObject;
	class GridComponent : public BaseComponent
	{
	public:
		GridComponent() = default;
		virtual void Start() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;

		void Initialize(float cellWidth, float cellHeight);
		Cell GetCell(glm::vec2 localPosition) const;
		Cell GetDestinationCell(glm::vec2 localPosition, glm::vec2 dir);
		~GridComponent();

	private:
		const int m_Rows{ 14 };
		const int m_Cols{ 18 };

		float m_CellWidth;
		float m_CellHeight;

		TextureComponent* m_pTexture;
		std::vector<Cell> m_Cells;
	};
}


