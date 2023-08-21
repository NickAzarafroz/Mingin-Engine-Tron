#include "GoToMainSceneCommand.h"
#include "ChangeModeCommand.h"
#include "GridComponent.h"
#include "EnemyComponent.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void GoToMainSceneCommand::Execute()
{
	if(SceneManager::GetInstance().GetCurrentSceneIndex() == 0)
	{
		SceneManager::GetInstance().LoadMainGame(ChangeModeCommand::m_ModeIndex);
		SceneManager::GetInstance().GoNextScene();
	}
}
