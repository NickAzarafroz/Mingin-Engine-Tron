#include "FPSComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"
using namespace dae;

FPSComponent::FPSComponent()
	: m_Fps{ 0 }, m_FrameCount{ 0 }
{

}

void FPSComponent::Start()
{
    m_pText = m_pGameObject->GetComponent<TextComponent>();
    m_LastFrameTime = SDL_GetTicks();
}

void FPSComponent::Update(float)
{
    Uint32 currentFrameTime = SDL_GetTicks();
    m_FrameCount++;
    if (currentFrameTime - m_LastFrameTime >= 1000)
    {
        m_Fps = m_FrameCount;
        m_FrameCount = 0;
        m_LastFrameTime = currentFrameTime;
    }

    m_pText->SetText(std::to_string(m_Fps) + " FPS");
}

void FPSComponent::Render() const
{
    m_pText->Render();
}

FPSComponent::~FPSComponent()
{

}
