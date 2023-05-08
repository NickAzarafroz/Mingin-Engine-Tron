#pragma once
#include <memory>
#include <string>
#include "BaseComponent.h"
#include "Transform.h"
#include "Texture2D.h"
#include "TransformComponent.h"

namespace dae
{
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent() = default;
		virtual void Start();
		virtual void Update(float elapsedSec) override;
		virtual void Render() const override;

		void SetPosition(float x, float y);
		void SetTexture(const std::string& filename);
		std::shared_ptr<Texture2D> GetTexture();
		Transform GetPosition();
		~TextureComponent();

	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};
	};
}