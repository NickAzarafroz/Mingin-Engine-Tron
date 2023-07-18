#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class GridComponent;
	class SpawnBulletCommand : public GameActorCommand
	{
	public:
		SpawnBulletCommand(GameObject* actor, std::vector<GameObject*> otherActors, GridComponent* pGrid) : GameActorCommand(actor), m_pOtherGameObjects{ otherActors }, m_pGrid{ pGrid } {}
		virtual ~SpawnBulletCommand() = default;

		SpawnBulletCommand(const SpawnBulletCommand& other) = delete;
		SpawnBulletCommand(SpawnBulletCommand&& other) = delete;
		SpawnBulletCommand& operator=(const SpawnBulletCommand& other) = delete;
		SpawnBulletCommand& operator=(SpawnBulletCommand&& other) = delete;

		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_GoBullet{};
		GridComponent* m_pGrid{};
		std::vector<GameObject*> m_pOtherGameObjects{};
	};
}

