#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
using namespace dae;

ScoreDisplayComponent::ScoreDisplayComponent()
    : m_Score{}
{

}

void ScoreDisplayComponent::Start()
{
    m_pText = m_pGameObject->GetComponent<TextComponent>();
    m_pText->SetText("Score: " + std::to_string(m_Score));
}

void ScoreDisplayComponent::Render() const
{
    m_pText->Render();
}

void dae::ScoreDisplayComponent::ReceiveMessage(int message)
{
    if(message == 0)
    {
        std::cout << "ScoreDisplayComponent: Message received\n";
    }
}

int dae::ScoreDisplayComponent::IncreaseScore()
{
    return ++m_Score;
}

ScoreDisplayComponent::~ScoreDisplayComponent()
{

}