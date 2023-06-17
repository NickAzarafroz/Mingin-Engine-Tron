#pragma once
#include "BaseComponent.h"
#include "Subject.h"
namespace dae
{
	class PlayerComponent : public BaseComponent
	{
	public:
		PlayerComponent() = default;
		virtual void Start() override;
		virtual void ReceiveMessage(int message) override;

		int GetHealth() const;
		void TakeDamage(int amount);
		~PlayerComponent();

		Subject<> healthChanged;

	private:
		int m_Health;
	};
}


