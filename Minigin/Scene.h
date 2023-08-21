#pragma once
#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class TextObject;
	class Scene final
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::shared_ptr<GameObject> object);
		void Remove(std::shared_ptr<GameObject> object);
		void RemoveAll();

		bool IsObjectInScene(std::shared_ptr<GameObject> object) const;

		const std::string& GetSceneName() const;
		std::vector <std::shared_ptr<GameObject>> GetAllObjects() const;

		void Start();
		void Update(float elapsedSec);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <std::shared_ptr<GameObject>> m_pObjects{};

		static unsigned int m_IdCounter; 
	};

}
