#include "Scene.h"
#include "GameObject.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_pObjects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_pObjects.erase(std::remove(m_pObjects.begin(), m_pObjects.end(), object), m_pObjects.end());
}

void Scene::RemoveAll()
{
	m_pObjects.clear();
}

bool Scene::IsObjectInScene(std::shared_ptr<GameObject> object) const
{
	for (const auto& obj : m_pObjects)
	{
		if (obj == object)
		{
			return true;
		}
	}
	return false;
}

const std::string& Scene::GetSceneName() const
{
	return m_Name;
}

std::vector<std::shared_ptr<GameObject>> Scene::GetAllObjects() const
{
	return m_pObjects;
}

void Scene::Start()
{
	for(auto& object : m_pObjects)
	{
		object->Start();
	}
}

void Scene::Update(float elapsedSec)
{
	for(size_t i{}; i < m_pObjects.size(); ++i)
	{
		m_pObjects[i]->Update(elapsedSec);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_pObjects)
	{
		object->Render();
	}
}

