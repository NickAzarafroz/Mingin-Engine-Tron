#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
using namespace dae;

void TextureComponent::Render() const 
{
	//const auto& transform = m_pGameObject->GetComponent<TransformComponent>();
	//const auto& pos = transform->GetPosition();

	// Render the active texture at the GameObject's position
	Renderer::GetInstance().RenderTexture(*m_Textures[m_ActiveTextureIndex], m_pGameObject->GetWorldPosition().x, m_pGameObject->GetWorldPosition().y, m_IsFlipped, m_Angle);
}

void dae::TextureComponent::ReceiveMessage(int message)
{
	if(message == 0)
	{
		std::cout << "TextureComponent: Message received\n";
	}
}

void TextureComponent::SetPosition(float x, float y)
{
	//m_transform.SetPosition(x, y, 0.0f);
	m_pGameObject->SetLocalPosition(glm::vec3(x, y, 0.0f));
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(filename));
}

void TextureComponent::AddTexture(const std::string& filename)
{
	// Load the texture and store it in the collection
	m_Textures.push_back(ResourceManager::GetInstance().LoadTexture(filename));
}

void TextureComponent::SetActiveTexture(int index)
{
	if (index >= 0 && index < static_cast<int>(m_Textures.size()))
	{
		// Set the active texture for rendering
		m_ActiveTextureIndex = index;
	}
}

std::shared_ptr<Texture2D> dae::TextureComponent::GetTexture()
{
	if (m_ActiveTextureIndex >= 0 && m_ActiveTextureIndex < static_cast<int>(m_Textures.size()))
	{
		return m_Textures[m_ActiveTextureIndex];
	}

	return nullptr;
}

Transform TextureComponent::GetPosition()
{
	return m_transform;
}

TextureComponent::~TextureComponent()
{

}