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
		bool IsOverlapping(GameObject* go);

		float GetWidth();
		float GetHeight();

	private:
		float m_Width;
		float m_Height;

		GameObject* m_pOtherObject;
	};
}


