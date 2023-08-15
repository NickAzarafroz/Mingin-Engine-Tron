#include "GoToNextSceneCommand.h"
#include "GridComponent.h"
#include "EnemyComponent.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void GoToNextSceneCommand::Execute()
{
	if (SceneManager::GetInstance().GetCurrentSceneIndex() == 1)
	{	
		for(const auto& object : SceneManager::GetInstance().GetScene(1).GetAllObjects())
		{
			if(object->GetComponent<EnemyComponent>())
			{
				object->MarkForDelete();
			}
		}
	}

	if(SceneManager::GetInstance().GetCurrentSceneIndex() == 0)
	{
		SceneManager::GetInstance().GoNextScene();
	}
}
