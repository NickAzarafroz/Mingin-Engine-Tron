#pragma once
#include "BaseComponent.h"
namespace dae
{
	class BoxColliderComponent : public BaseComponent
	{
	public:
		BoxColliderComponent() = default;
		virtual void Start() override;
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;

		~BoxColliderComponent();

	private:
	};
}


