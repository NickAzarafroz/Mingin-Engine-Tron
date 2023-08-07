#pragma once
#include "BaseComponent.h"
namespace dae
{
	class EnemyComponent : public BaseComponent
	{
	public:
		EnemyComponent() = default;
		~EnemyComponent() = default;

		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

		virtual void Start() override;
		virtual void Update(float elapsedSec) override;
		virtual void ReceiveMessage(int message) override;

		void SetPlayer(GameObject* pPlayer);
		int GetHealth() const;
		void TakeDamage(int amount);
		void Destroy();

	private:
		int m_Health;
		GameObject* m_pPlayer;
	};
}

