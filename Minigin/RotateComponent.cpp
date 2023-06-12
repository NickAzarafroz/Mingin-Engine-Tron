#include "TextureComponent.h"
#include "RotateComponent.h"

void dae::RotateComponent::Start()
{
	//m_pTransform = m_pGameObject->GetComponent<TransformComponent>();
	m_CenterX = m_pGameObject->GetWorldPosition().x;
	m_CenterY = m_pGameObject->GetWorldPosition().y;
}

void dae::RotateComponent::Update(float elapsedSec)
{
	float x = m_CenterX + cos(m_Angle) * m_Radius;
	float y = m_CenterY + sin(m_Angle) * m_Radius;

	m_pGameObject->SetLocalPosition(glm::vec3(x, y, 0.0f));

	m_Angle += m_Speed * elapsedSec;
}

void dae::RotateComponent::Render() const
{
}

void dae::RotateComponent::ReceiveMessage(int message)
{
	if(message == 0)
	{
		std::cout << "RotateComponent: Message Received\n";
	}
}

void dae::RotateComponent::SetRadius(float radius)
{
	m_Radius = radius;
}

void dae::RotateComponent::SetSpeed(float speed)
{
	m_Speed = speed;
}

dae::RotateComponent::~RotateComponent()
{
}
