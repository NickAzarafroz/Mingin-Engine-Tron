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
	for(std::shared_ptr<GameObject> other : m_pOthers)
	{
		if (IsOverlapping(other))
		{
			if (m_ConditionHealth)
			{
				if (m_pGameObject->GetComponent<EnemyComponent>())
				{
					m_pGameObject->GetComponent<EnemyComponent>()->TakeDamage(1);
				}
				else
				{
					m_pGameObject->GetComponent<PlayerComponent>()->TakeDamage(1);
				}
			}

			if (m_ConditionPlayer)
			{
				other->GetComponent<TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
				other->GetComponent<PlayerComponent>()->TakeDamage(1);

				MoveGridCommand::m_MovementFlag = false;
				MoveGridCommandP2::m_MovementFlag = false;
				SceneManager::GetInstance().ResetEnemies();
			}

			if (m_ConditionOther)
			{
				if(other->GetComponent<PlayerComponent>())
				{
					other->GetComponent<TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
					other->GetComponent<PlayerComponent>()->TakeDamage(1);

					MoveGridCommand::m_MovementFlag = false;
					MoveGridCommandP2::m_MovementFlag = false;
					SceneManager::GetInstance().ResetEnemies();
					return;
				}

				other->GetComponent<TransformComponent>()->SetPosition(0.f, -50.f, 0.f);
				other->RemoveGameObject();
			}

			if (m_ConditionMe)
			{
				m_pGameObject->MarkForDelete();
			}
		}
	}
}

void BoxTriggerComponent::SetSize(float width, float height)
{
	m_Width = width;
	m_Height = height;
}

void BoxTriggerComponent::AddOtherObject(std::shared_ptr<GameObject> go)
{
	/*for (const auto& other : m_pOthers)
	{
		if (other == go) return;
	}*/

	for (int i{}; i < m_pOthers.size(); ++i)
	{
		if (m_pOthers[i] == go) return;
	}

	m_pOthers.emplace_back(go);
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

bool BoxTriggerComponent::IsOverlapping(std::shared_ptr<GameObject> go)
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
