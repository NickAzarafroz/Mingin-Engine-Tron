#include "LiveDisplayComponent.h"
#include "TextComponent.h"
#include "PlayerComponent.h"
using namespace dae;

LiveDisplayComponent::LiveDisplayComponent()
{
  
}

void LiveDisplayComponent::SetObjectToDisplayLives(GameObject* go)
{
    m_pPlayer = go->GetComponent<PlayerComponent>();
}

void LiveDisplayComponent::Start()
{
    m_pText = m_pGameObject->GetComponent<TextComponent>();

    m_pPlayer->healthChanged.AddObserver(this);
    m_HealthPoints = m_pPlayer->GetHealth();

    m_pText->SetText("HealthPoints " + std::to_string(m_HealthPoints));
}

void LiveDisplayComponent::Render() const
{
    m_pText->Render();
}

void dae::LiveDisplayComponent::ReceiveMessage(int message)
{
    if(message == 0)
    {
        std::cout << "LiveDisplayComponent: Message received\n";
    }
}

LiveDisplayComponent::~LiveDisplayComponent()
{
    m_pPlayer->healthChanged.RemoveObserver(this);
}

void LiveDisplayComponent::HandleEvent()
{
    --m_HealthPoints;
    m_pText->SetText("HealthPoints " + std::to_string(m_HealthPoints));
}

void LiveDisplayComponent::OnSubjectDestroy()
{
   
}
