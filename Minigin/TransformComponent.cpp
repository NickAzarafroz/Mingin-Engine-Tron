#include "TransformComponent.h"
using namespace dae;

void dae::TransformComponent::ReceiveMessage(int message)
{
	if(message == 0)
	{
		std::cout << "TransformComponent: Message received\n";
	}
}

void TransformComponent::SetPosition(float x, float y, float z)
{
	m_Transform.x = x;
	m_Transform.y = y;
	m_Transform.z = z;

	m_pGameObject->SetLocalPosition(glm::vec3{ x, y, z });
}

const glm::vec3& TransformComponent::GetPosition() const
{
	return m_Transform;
}

TransformComponent::~TransformComponent()
{

}