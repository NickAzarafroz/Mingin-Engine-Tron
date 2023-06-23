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
		~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		virtual void Render() const override;
		virtual void ReceiveMessage(int message) override;

		void SetPosition(float x, float y);
		void SetTexture(const std::string& filename);
		void AddTexture(const std::string& filename);
		void SetActiveTexture(int index);

		void SetFlipped(bool flip) { m_IsFlipped = flip; };
		bool GetFlipped() { return m_IsFlipped; };

		void SetAngle(float angle) { m_Angle = angle; };
		float GetAngle() { return m_Angle; };

		std::shared_ptr<Texture2D> GetTexture();
		Transform GetPosition();

	private:
		Transform m_transform{};
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::shared_ptr<Texture2D>> m_Textures;
		int m_ActiveTextureIndex;
		bool m_IsFlipped;
		float m_Angle;
	};
}