#include "GoToNextSceneCommand.h"
#include "SceneManager.h"
using namespace dae;

void GoToNextSceneCommand::Execute()
{
	if(SceneManager::GetInstance().GetCurrentSceneIndex() == 0)
	{
		SceneManager::GetInstance().GoNextScene();
	}
}
