#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "EventSystem.h"
#include <iostream>

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	for (const auto& component : m_pComponents)
	{
		component->Start();
	}
}

void dae::GameObject::Update(float elapsedSec)
{
	for(const auto& component : m_pComponents)
	{
		component->Update(elapsedSec);
	}

	/*for (const auto& child : m_pChildren)
	{
		child->Update(elapsedSec);
	}*/

	m_ElapsedSec = elapsedSec;
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		component->Render();
	}

	/*for (const auto& child : m_pChildren)
	{
		child->Render();
	}*/
}

void dae::GameObject::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}

const glm::vec3& dae::GameObject::GetLocalPosition()
{
	return m_LocalPosition;
}

void dae::GameObject::UpdateWorldPosition()
{
	if(m_PositionIsDirty)
	{
		if(m_pParent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			m_WorldPosition = m_pParent->GetWorldPosition() + m_LocalPosition;
		}
	}

	m_PositionIsDirty = false;
}

const glm::vec3& dae::GameObject::GetWorldPosition()
{
	if(m_PositionIsDirty)
	{
		UpdateWorldPosition();
	}

	return m_WorldPosition;
}

void dae::GameObject::SetPositionDirty()
{
	m_PositionIsDirty = true;

	for(const auto& child : m_pChildren)
	{
		child->SetPositionDirty();
	}
}

void dae::GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	if(pParent == nullptr)
	{
		SetLocalPosition(GetWorldPosition());
	}
	else
	{
		if(keepWorldPosition)
		{
			SetLocalPosition(GetLocalPosition() - pParent->GetWorldPosition());
			SetPositionDirty();
		}
	}

	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}

	m_pParent = pParent;

	if (m_pParent)
	{
		m_pParent->AddChild(this);
	}

	/*if(m_pParent == nullptr)
	{
		m_pParent = pParent;
		m_pParent->AddChild(this);
	}
	else
	{
		m_pParent->RemoveChild(this);
		m_pParent = pParent;
		m_pParent->AddChild(this);
	}*/
}

void dae::GameObject::AddChild(GameObject* pChild)
{
	if (pChild->m_pParent) 
	{
		pChild->m_pParent->RemoveChild(pChild);
	}

	pChild->m_pParent = this;

	m_pChildren.push_back(pChild);
}

void dae::GameObject::RemoveChild(GameObject* pChild)
{
	for(size_t idx{}; idx < m_pChildren.size(); ++idx)
	{
		if(m_pChildren[idx] == pChild)
		{
			m_pChildren.erase(m_pChildren.begin() + idx);
		}
	}

	pChild->m_pParent = nullptr;
}

void dae::GameObject::GetAllChildren()
{
	for(const auto& child : m_pChildren)
	{
		std::cout << "{ " << child->GetWorldPosition().x << "," << child->GetWorldPosition().y << " }" << '\n';
	}
}


