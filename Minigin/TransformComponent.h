#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent() = default;
		~TransformComponent();

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) = delete;

		virtual void ReceiveMessage(int message) override;

		void SetPosition(float x, float y, float z);
		const glm::vec3& GetPosition() const;

	private:
		glm::vec3 m_Transform{};
	};
}