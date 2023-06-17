#pragma once
#include <SDL.h>
#include <string>
#include "BaseComponent.h"
namespace dae
{
	class TextComponent;
	class ScoreDisplayComponent : public BaseComponent
	{
	public:
		ScoreDisplayComponent();
		~ScoreDisplayComponent();

		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

		virtual void Start();
		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;
		int IncreaseScore();

	private:
		int m_Score;
		TextComponent* m_pText{};
	};
}
