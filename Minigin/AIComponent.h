#pragma once
#include "BaseComponent.h"
#include "GridComponent.h"
#include "glm/glm.hpp"
#include <memory>
namespace dae
{
	struct Cell;
	class GridComponent;
	class AIComponent : public BaseComponent
	{
	public:
		AIComponent() = default;
		~AIComponent() = default;

		AIComponent(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent& operator=(AIComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

		void SetObjectToShoot(std::shared_ptr<GameObject> pPlayer);
		void SetGrid(GridComponent* pGrid);
		void SetSpeed(float speed);
		void SetMovementFlag(bool flag);

	private:
		void Wander();
		void ShootPlayer();

		glm::vec2 m_Dir{0.f, 0.f};
		GridComponent* m_pGrid{};
		std::shared_ptr<GameObject> m_pPlayer{};
		std::shared_ptr<GameObject> m_pGoBullet{};

		float m_Speed{ 25.f };

		bool m_MovementFlag;
		bool m_IsValid;
		glm::vec2 m_TempDir;
		Cell m_Cell;
		Cell m_DestinationCell;
	};
}
