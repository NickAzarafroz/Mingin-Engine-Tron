#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "TextComponent.h"
#include "TransformComponent.h"

using namespace dae;

TextComponent::TextComponent()
	: m_needsUpdate(true), m_textTexture(nullptr), m_Color{ 255,255,255 }
{
	
}

void TextComponent::Start()
{
}

void TextComponent::Update(float)
{
	if (m_needsUpdate)
	{
		//m_Color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void TextComponent::Render() const
{
	if (m_textTexture != nullptr)
	{
		//const auto& transform = m_pGameObject->GetComponent<TransformComponent>();
		//const auto& pos = transform->GetPosition();

		Renderer::GetInstance().RenderTexture(*m_textTexture, m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y);
	}
}

void dae::TextComponent::ReceiveMessage(int message)
{
	if(message == 0)
	{
		std::cout << "TextComponent: Message received\n";
	}
}

void TextComponent::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}

void TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_font = font;
}

void dae::TextComponent::SetFontColor(Uint8 r, Uint8 g, Uint8 b)
{
	m_Color = { r, g, b };
}

TextComponent::~TextComponent()
{

}
