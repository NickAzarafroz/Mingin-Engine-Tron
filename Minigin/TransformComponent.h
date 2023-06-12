#pragma once
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent() = default;

		virtual void Start();
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;

		void SetPosition(float x, float y, float z);
		const glm::vec3& GetPosition() const;

		~TransformComponent();

	private:
		glm::vec3 m_Transform{};
	};
}