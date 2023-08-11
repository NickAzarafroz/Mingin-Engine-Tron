#pragma once
#include "BaseComponent.h"
#include "GridComponent.h"
#include "glm/glm.hpp"
#include <vector>
#include <map>
namespace dae
{
	struct Cell;
	class GridComponent;
	class ValidCellComponent : public BaseComponent
	{
	public:
		ValidCellComponent() = default;
		~ValidCellComponent() = default;

		ValidCellComponent(const ValidCellComponent& other) = delete;
		ValidCellComponent(ValidCellComponent&& other) = delete;
		ValidCellComponent& operator=(const ValidCellComponent& other) = delete;
		ValidCellComponent& operator=(ValidCellComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

		void SetGrid(GridComponent* m_pGrid);
		void SetDirection(glm::vec2 dir);
		void IncreaseBounce();

		void SetBounceThreshold(int amount);
		int GetAmountBounce();

	private:
		GridComponent* m_pGrid{};
		std::vector<Cell> m_BulletTrail{};
		Cell m_CurrentCell;
		glm::vec2 m_Dir{};
		int m_CellID{ 0 };
		int m_AmountBounce{};
		int m_BounceThreshold{};
	};
}


