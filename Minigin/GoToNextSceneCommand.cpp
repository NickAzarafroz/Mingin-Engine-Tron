#include "GoToNextSceneCommand.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void GoToNextSceneCommand::Execute()
{
	if (SceneManager::GetInstance().GetCurrentSceneIndex() == 1)
	{	
		SceneManager::GetInstance().GetScene(0).RemoveAll();
		SceneManager::GetInstance().GetScene(1).RemoveAll();

		SceneManager::GetInstance().Initialize();
	}

	if(SceneManager::GetInstance().GetCurrentSceneIndex() == 0)
	{
		SceneManager::GetInstance().GoNextScene();
	}
}
