#include "BoxTriggerComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "MoveGridCommand.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void BoxTriggerComponent::Update(float)
{
	if (IsOverlapping(m_pOtherObject))
	{
		if(m_ConditionHealth)
		{
			m_pGameObject->GetComponent<EnemyComponent>()->TakeDamage(1);
		}

		if(m_ConditionPlayer)
		{
			m_pOtherObject->GetComponent<TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
			m_pOtherObject->GetComponent<PlayerComponent>()->TakeDamage(1);

			MoveGridCommand::m_MovementFlag = false;
			SceneManager::GetInstance().ResetEnemies();
		}

		if (m_ConditionOther)
		{
			m_pOtherObject->MarkForDelete();
			m_pOtherObject = nullptr;
		}

		if (m_ConditionMe) 
		{
			m_pGameObject->MarkForDelete();
		} 
	}
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

void BoxTriggerComponent::SetPlayerObject(GameObject* pPlayer)
{
	m_pPlayer = pPlayer;
}

void BoxTriggerComponent::DestroyOtherAfterOverLap(bool condition)
{
	m_ConditionOther = condition;
}

void BoxTriggerComponent::DestroyMeAfterOverLap(bool condition)
{
	m_ConditionMe = condition;
}

void BoxTriggerComponent::DecMyHealthAfterOverlap(bool condition)
{
	m_ConditionHealth = condition;
}

void dae::BoxTriggerComponent::DecOtherHealthAfterOverlap(bool condition)
{
	m_ConditionPlayer = condition;
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
