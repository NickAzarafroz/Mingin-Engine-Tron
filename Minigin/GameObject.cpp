#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Scene.h"
#include <iostream>

dae::GameObject::GameObject(Scene* pScene)
	: m_LocalPosition{}, m_WorldPosition{}, m_PositionIsDirty{},
	  m_pComponents{}, m_pParent{}, m_pChildren{}, m_pScene{pScene},
	  m_ElapsedSec{}
{

}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	for (const auto& component : m_pComponents)
	{
		component->Start();
	}

	for (const auto& child : m_pChildren)
	{
		child->Start();
	}
}

void dae::GameObject::Update(float elapsedSec)
{
	if (this == nullptr) return;

	for(const auto& component : m_pComponents)
	{
		if (m_MarkedForDelete)
		{
			this->RemoveGameObject();
			return;
		}
		component->Update(elapsedSec);
	}

	for (const auto& child : m_pChildren)
	{
		child->Update(elapsedSec);
	}

	m_ElapsedSec = elapsedSec;
}

void dae::GameObject::Render() const
{
	for (const auto& component : m_pComponents)
	{
		if (m_MarkedForDelete) return;
		component->Render();
	}

	for (const auto& child : m_pChildren)
	{
		child->Render();
	}
}

void dae::GameObject::SendMessageID(int message)
{
	for (const auto& component : m_pComponents)
	{
		component->ReceiveMessage(message);
	}
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
		}
		SetPositionDirty();
	}

	if (m_pParent)
	{
		m_pParent->RemoveChild(shared_from_this());
	}

	m_pParent = pParent;

	if (m_pParent)
	{
		m_pParent->AddChild(shared_from_this());
	}
}

void dae::GameObject::RemoveGameObject()
{
	if(m_pParent)
	{
		m_pParent->RemoveChild(shared_from_this());
	}

	m_pScene->Remove(shared_from_this());
}

void dae::GameObject::AddGameObject()
{
	m_pScene->Add(shared_from_this());
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> pChild)
{
	pChild->m_pParent->m_pChildren.emplace_back(pChild);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> pChild)
{
	auto it = std::find(m_pChildren.begin(), m_pChildren.end(), pChild);
	if (it != m_pChildren.end())
	{
		m_pChildren.erase(it);
	}
}

void dae::GameObject::GetAllChildren()
{
	for(const auto& child : m_pChildren)
	{
		std::cout << "{ " << child->GetWorldPosition().x << "," << child->GetWorldPosition().y << " }" << '\n';
	}
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAtIndex(int index)
{
	for(int i{}; i < m_pChildren.size(); ++i)
	{
		if(i == index)
		{
			return m_pChildren[i];
		}
	}

	return nullptr;
}

void dae::GameObject::MarkForDelete()
{
	m_MarkedForDelete = true;
}

void dae::GameObject::UnmarkForDelete()
{
	m_MarkedForDelete = false;
}

bool dae::GameObject::IsDeleted()
{
	return m_MarkedForDelete;
}


