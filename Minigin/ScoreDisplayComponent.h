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
		virtual void Start();
		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;
		int IncreaseScore();
		~ScoreDisplayComponent();

	private:
		int m_Score;
		TextComponent* m_pText{};
	};
}
