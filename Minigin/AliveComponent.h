#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class AliveComponent : public BaseComponent
	{
	public:
		AliveComponent() = default;
		~AliveComponent() = default;

		AliveComponent(const AliveComponent& other) = delete;
		AliveComponent(AliveComponent&& other) = delete;
		AliveComponent& operator=(const AliveComponent& other) = delete;
		AliveComponent& operator=(AliveComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

		void CheckIfEnemiesAlive(bool condition);
		void CheckIfPlayerAlive(bool condition);
		void CheckIfOnePlayerAlive(bool condition);
		void AddPlayersToCheck(std::shared_ptr<GameObject> pPlayer);

	private:
		bool m_EnemiesCondition{};
		bool m_PlayerCondition{};
		bool m_OnePlayerCondition{};
		int m_CurrentScore{};

		std::vector<std::shared_ptr<GameObject>> m_pPlayers{};
	};
}

