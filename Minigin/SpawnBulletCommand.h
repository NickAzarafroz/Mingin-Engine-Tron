#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class GridComponent;
	class SpawnBulletCommand : public GameActorCommand
	{
	public:
		SpawnBulletCommand(GameObject* actor, GameObject* otherActor, GridComponent* pGrid) : GameActorCommand(actor), m_pOtherGameObject{ otherActor }, m_pGrid{ pGrid } {}
		virtual ~SpawnBulletCommand() = default;

		SpawnBulletCommand(const SpawnBulletCommand& other) = delete;
		SpawnBulletCommand(SpawnBulletCommand&& other) = delete;
		SpawnBulletCommand& operator=(const SpawnBulletCommand& other) = delete;
		SpawnBulletCommand& operator=(SpawnBulletCommand&& other) = delete;

		void Execute() override;

	private:
		std::shared_ptr<GameObject> m_GoBullet{};
		GridComponent* m_pGrid{};
		GameObject* m_pOtherGameObject{};
	};
}

