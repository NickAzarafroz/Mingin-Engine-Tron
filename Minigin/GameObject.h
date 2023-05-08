#pragma once
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class GameObject final
	{
	public:
		void Start();
		void Update(float elapsedSec);
		void Render() const;

		float GetElapsedSec() { return m_ElapsedSec; };

		void SetLocalPosition(const glm::vec3& pos);
		const glm::vec3& GetLocalPosition();

		void UpdateWorldPosition();
		const glm::vec3& GetWorldPosition();

		void SetPositionDirty();

		void SetParent(GameObject* pParent, bool keepWorldPosition);
		void GetAllChildren();

		template <typename T>
		T* AddComponent();

		template <typename T>
		void RemoveComponent();

		template <typename T>
		T* GetComponent() const;

		template <typename T>
		bool HasComponent() const;

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
		bool m_PositionIsDirty;

		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

		GameObject* m_pParent{};
		std::vector<GameObject*> m_pChildren;

		float m_ElapsedSec;
	};

	template<typename T>
	inline T* GameObject::AddComponent()
	{
		m_pComponents.emplace_back(std::make_shared<T>());
		m_pComponents.back()->SetGameObject(*this);

		return static_cast<T*>(m_pComponents.back().get());
	}

	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		for (size_t idx{}; idx < m_pComponents.size(); ++idx)
		{
			if (dynamic_cast<T*>(m_pComponents[idx].get()))
			{
				m_pComponents.erase(m_pComponents.begin() + idx);
				break;
			}
		}
	}

	template <typename T>
	inline T* dae::GameObject::GetComponent() const
	{
		for (const auto& component : m_pComponents)
		{
			T* result = dynamic_cast<T*>(component.get());

			if (result)
			{
				return result;
			}
		}

		return nullptr;
	}

	template <typename T>
	inline bool dae::GameObject::HasComponent() const
	{
		for (const auto& component : m_pComponents)
		{
			if (dynamic_cast<T*>(component.get()))
			{
				return true;
			}
		}

		return false;
	}
}
