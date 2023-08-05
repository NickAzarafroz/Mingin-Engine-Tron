#include "SceneManager.h"
#include "Scene.h"
#include "MainMenuScene.h"
#include "TronGameScene.h"

void dae::SceneManager::Start()
{
	for (auto& scene : m_scenes)
	{
		scene->Start();
	}
}

void dae::SceneManager::Update(float elapsedSec)
{
	m_scenes[m_ActiveSceneIndex]->Update(elapsedSec);
}

void dae::SceneManager::Render()
{
	m_scenes[m_ActiveSceneIndex]->Render();
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

dae::Scene& dae::SceneManager::GetScene(int index)
{
	Scene* scene{ m_scenes[index].get() };
	return *scene;
}

void dae::SceneManager::Initialize()
{
	m_MainMenuScene = std::make_shared<MainMenuScene>(m_scenes[0]);
	m_MainMenuScene->Load();

	m_TronGameScene = std::make_shared<TronGameScene>(m_scenes[1]);
	m_TronGameScene->Load();
}

void dae::SceneManager::GoNextScene()
{
	++m_ActiveSceneIndex;
}

int dae::SceneManager::GetCurrentSceneIndex()
{
	return m_ActiveSceneIndex;
}
