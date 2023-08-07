#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
using namespace dae;

ScoreDisplayComponent::ScoreDisplayComponent()
{

}

void ScoreDisplayComponent::SetObjectToDisplayScore(GameObject* go)
{
    m_pPlayer = go->GetComponent<PlayerComponent>();
}

void ScoreDisplayComponent::Start()
{
    m_pText = m_pGameObject->GetComponent<TextComponent>();

    m_pPlayer->scoreChanged.AddObserver(this);
    m_Score = m_pPlayer->GetScore();

    m_pText->SetText(std::to_string(m_Score));
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

void dae::ScoreDisplayComponent::HandleEvent()
{
    m_Score = m_pPlayer->GetScore();
    m_pText->SetText(std::to_string(m_Score));
}

void dae::ScoreDisplayComponent::OnSubjectDestroy()
{
   
}

ScoreDisplayComponent::~ScoreDisplayComponent()
{
    m_pPlayer->scoreChanged.RemoveObserver(this);
}