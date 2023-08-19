#pragma once
#include <string>
#include <memory>
#include <SDL_stdinc.h>
#include <SDL.h>
#include "Transform.h"
#include "ResourceManager.h"
#include "BaseComponent.h"
#include "GameObject.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent();
		~TextComponent();

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetFontColor(Uint8 r, Uint8 g, Uint8 b);

	private:
		bool m_needsUpdate;
		bool m_flip{ false };
		std::string m_text;
		std::shared_ptr<Font> m_font{};
		std::shared_ptr<Texture2D> m_textTexture;
		Transform m_transform{};
		SDL_Color m_Color;
	};
}

