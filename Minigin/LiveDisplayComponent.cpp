#include "LiveDisplayComponent.h"
#include "TextComponent.h"
using namespace dae;

LiveDisplayComponent::LiveDisplayComponent()
	: m_HealthPoints{ 500 }
{

}

void LiveDisplayComponent::Start()
{
    m_pText = m_pGameObject->GetComponent<TextComponent>();
    m_pText->SetText("HealthPoints: " + std::to_string(m_HealthPoints));
}

void LiveDisplayComponent::Update(float)
{
}

void LiveDisplayComponent::Render() const
{
    m_pText->Render();
}

int dae::LiveDisplayComponent::DecreaseLive()
{
    if(m_HealthPoints > 0)
    {
        return --m_HealthPoints;
    }
    return 0;
}

LiveDisplayComponent::~LiveDisplayComponent()
{
    
}
