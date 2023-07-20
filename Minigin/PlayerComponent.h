#pragma once
#include "BaseComponent.h"
#include "Subject.h"
namespace dae
{
	class PlayerComponent : public BaseComponent
	{
	public:
		PlayerComponent() = default;
		~PlayerComponent();

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) = delete;

		virtual void Start() override;
		virtual void Update(float elapsedSec) override;
		virtual void ReceiveMessage(int message) override;

		int GetHealth() const;
		int GetScore() const;

		void TakeDamage(int amount);
		void IncreaseScore(int amount);
		void Destroy();

		Subject<> healthChanged;
		Subject<> scoreChanged;

	private:
		int m_Health;
		int m_Score;
	};
}


