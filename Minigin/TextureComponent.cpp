#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
using namespace dae;

void TextureComponent::Start(){}

void TextureComponent::Update(float) {};

void TextureComponent::Render() const 
{
	//const auto& transform = m_pGameObject->GetComponent<TransformComponent>();
	//const auto& pos = transform->GetPosition();

	Renderer::GetInstance().RenderTexture(*m_texture, m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y);
};

void TextureComponent::SetPosition(float x, float y)
{
	//m_transform.SetPosition(x, y, 0.0f);
	m_pGameObject->SetLocalPosition(glm::vec3(x, y, 0.0f));
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

std::shared_ptr<Texture2D> dae::TextureComponent::GetTexture()
{
	return m_texture;
}

Transform TextureComponent::GetPosition()
{
	return m_transform;
}

TextureComponent::~TextureComponent()
{

}