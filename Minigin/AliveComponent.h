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

	private:
		bool m_EnemiesCondition{};
	};
}

