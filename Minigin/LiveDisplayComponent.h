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
		~LiveDisplayComponent();

		LiveDisplayComponent(const LiveDisplayComponent& other) = delete;
		LiveDisplayComponent(LiveDisplayComponent&& other) = delete;
		LiveDisplayComponent& operator=(const LiveDisplayComponent& other) = delete;
		LiveDisplayComponent& operator=(LiveDisplayComponent&& other) = delete;

		void SetObjectToDisplayLives(GameObject* go);

		virtual void Start();
		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;

	private:
		int m_HealthPoints{};
		TextComponent* m_pText{};
		PlayerComponent* m_pPlayer{};

		virtual void HandleEvent() override;
		virtual void OnSubjectDestroy() override;
	};
}

