#pragma once
#include "BaseComponent.h"

namespace dae
{
	//class TransformComponent;
	class RotateComponent : public BaseComponent
	{
	public:
		RotateComponent() = default;
		~RotateComponent();

		RotateComponent(const RotateComponent& other) = delete;
		RotateComponent(RotateComponent&& other) = delete;
		RotateComponent& operator=(const RotateComponent& other) = delete;
		RotateComponent& operator=(RotateComponent&& other) = delete;

		virtual void Start();
		virtual void Update(float elapsedSec) override;
		virtual void ReceiveMessage(int message) override;

		void SetRadius(float radius);
		void SetSpeed(float speed);

	private:
		//TransformComponent* m_pTransform{};

		float m_Speed{};
		float m_Radius{};
		float m_CenterX{};
		float m_CenterY{};
		float m_Angle{};
	};
}


