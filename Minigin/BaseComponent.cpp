#include "BaseComponent.h"
using namespace dae;

void BaseComponent::SetGameObject(GameObject& gameObject)
{
	m_pGameObject = &gameObject;
}

GameObject* BaseComponent::GetGameObject() const
{
	return m_pGameObject;
}
