#pragma once
#include <SDL.h>
#include <string>
#include "BaseComponent.h"
#include "Observer.h"
namespace dae
{
	class PlayerComponent;
	class TextComponent;
	class ScoreDisplayComponent final : public BaseComponent, public Observer<>
	{
	public:
		ScoreDisplayComponent();
		~ScoreDisplayComponent();

		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

		void SetObjectToDisplayScore(GameObject* go);

		virtual void Start();
		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;

	private:
		int m_Score;
		TextComponent* m_pText{};
		PlayerComponent* m_pPlayer{};

		virtual void HandleEvent() override;
		virtual void OnSubjectDestroy() override;
	};
}
