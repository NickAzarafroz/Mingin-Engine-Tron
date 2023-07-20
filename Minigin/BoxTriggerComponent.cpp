#include "BoxTriggerComponent.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
using namespace dae;

void BoxTriggerComponent::Update(float)
{
	IsOverlapping(m_pOtherObject);
}

void BoxTriggerComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void BoxTriggerComponent::SetOtherObject(GameObject* go)
{
	m_pOtherObject = go;
}

void BoxTriggerComponent::SetPlayerObject(GameObject* player)
{
	m_pPlayerObject = player;
}

bool BoxTriggerComponent::IsOverlapping(GameObject* go)
{
	if (go == nullptr) return false;

	if ((m_pGameObject->GetLocalPosition().x + m_Width) < go->GetLocalPosition().x || (go->GetLocalPosition().x + go->GetComponent<BoxTriggerComponent>()->GetWidth()) < m_pGameObject->GetLocalPosition().x)
	{
		return false;
	}

	if (m_pGameObject->GetLocalPosition().y > (go->GetLocalPosition().y + go->GetComponent<BoxTriggerComponent>()->GetHeight()) || go->GetLocalPosition().y > (m_pGameObject->GetLocalPosition().y + m_Height))
	{
		return false;
	}

	go->RemoveGameObject();
	m_pGameObject->GetComponent<PlayerComponent>()->TakeDamage(1);
	if (m_pPlayerObject) 
	{
		m_pPlayerObject->GetComponent<PlayerComponent>()->IncreaseScore(3);
	} 
	m_pOtherObject = nullptr;
	return true;
}

float BoxTriggerComponent::GetWidth()
{
	return m_Width;
}

float BoxTriggerComponent::GetHeight()
{
	return m_Height;
}
