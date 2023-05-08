#pragma once
#include <SDL.h>
#include <string>
#include "BaseComponent.h"
namespace dae
{
	class TextComponent;
	class LiveDisplayComponent : public BaseComponent
	{
	public:
		LiveDisplayComponent();
		virtual void Start();
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
		int DecreaseLive();
		~LiveDisplayComponent();

	private:
		int m_HealthPoints;
		TextComponent* m_pText{};
	};
}

