#pragma once
#include <SDL.h>
#include <string>
#include "BaseComponent.h"
#include "Observer.h"
namespace dae
{
	class PlayerComponent;
	class TextComponent;
	class LiveDisplayComponent final : public BaseComponent, public Observer<>
	{
	public:
		LiveDisplayComponent();
		virtual void Start();
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
		~LiveDisplayComponent();

	private:
		int m_HealthPoints{};
		TextComponent* m_pText{};
		PlayerComponent* m_pPlayer{};

		virtual void HandleEvent() override;
		virtual void OnSubjectDestroy() override;
	};
}

