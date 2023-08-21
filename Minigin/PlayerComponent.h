#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include <string>
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
		std::string GetName() const;

		void TakeDamage(int amount);
		void IncreaseScore(int amount);
		void Destroy();
		void SetName(std::string name);

		Subject<> healthChanged;
		Subject<> scoreChanged;

	private:
		int m_Health;
		int m_Score;
		std::string m_Name;
	};
}


