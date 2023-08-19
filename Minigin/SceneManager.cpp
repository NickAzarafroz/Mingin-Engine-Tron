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
	m_TronGameScene = std::make_shared<TronGameScene>(m_scenes[1]);

	m_MainMenuScene->Load();
}

void dae::SceneManager::ResetEnemies()
{
	m_TronGameScene->ResetEnemies();
}

void dae::SceneManager::LoadLevel1()
{
	m_TronGameScene->LoadLevel1();
}

void dae::SceneManager::LoadLevel2()
{
	m_TronGameScene->LoadLevel2();
}

void dae::SceneManager::LoadLevel3()
{
	m_TronGameScene->LoadLevel3();
}

void dae::SceneManager::GoNextScene()
{
	++m_ActiveSceneIndex;
}

int dae::SceneManager::GetCurrentSceneIndex()
{
	return m_ActiveSceneIndex;
}

void dae::SceneManager::SetCurrentSceneIndex(int index)
{
	m_ActiveSceneIndex = index;
}

int dae::SceneManager::GetLevel()
{
	return m_TronGameScene->GetLevel();
}

void dae::SceneManager::LoadMainGame(int mode)
{
	switch (mode)
	{
	case 0: m_TronGameScene->LoadSinglePlayer();
		break;
	case 1: m_TronGameScene->LoadVersus();
		break;
	case -1: m_TronGameScene->LoadCoop();
		break;
	default:
		break;
	}
}
