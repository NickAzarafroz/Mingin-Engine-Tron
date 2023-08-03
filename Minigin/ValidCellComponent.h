#pragma once
#include "BaseComponent.h"
#include "glm/glm.hpp"
namespace dae
{
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
		bool m_IsValid{ true };
		glm::vec2 m_Dir{};
		bool m_HasCollided{};
		int m_AmountBounce{};
		int m_BounceThreshold{};
	};
}


