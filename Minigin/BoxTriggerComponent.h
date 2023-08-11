#pragma once
#include "BaseComponent.h"
namespace dae
{
	class BoxTriggerComponent : public BaseComponent
	{
	public:
		BoxTriggerComponent() = default;
		~BoxTriggerComponent() = default;

		BoxTriggerComponent(const BoxTriggerComponent& other) = delete;
		BoxTriggerComponent(BoxTriggerComponent&& other) = delete;
		BoxTriggerComponent& operator=(const BoxTriggerComponent& other) = delete;
		BoxTriggerComponent& operator=(BoxTriggerComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

		void SetSize(float width, float height);
		void SetOtherObject(GameObject* go);
		void SetPlayerObject(GameObject* pPlayer);

		void DestroyOtherAfterOverLap(bool condition);
		void DestroyMeAfterOverLap(bool condition);

		void DecMyHealthAfterOverlap(bool condition);
		void DecOtherHealthAfterOverlap(bool condition);

		float GetWidth();
		float GetHeight();

	private:
		bool IsOverlapping(GameObject* go);

		float m_Width;
		float m_Height;

		bool m_ConditionOther;
		bool m_ConditionMe;
		bool m_ConditionHealth;
		bool m_ConditionPlayer;

		GameObject* m_pOtherObject;
		GameObject* m_pPlayer;
	};
}


