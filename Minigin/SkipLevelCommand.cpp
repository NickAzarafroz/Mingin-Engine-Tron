#include "SkipLevelCommand.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EnemyComponent.h"
using namespace dae;

void SkipLevelCommand::Execute()
{
	if (SceneManager::GetInstance().GetCurrentSceneIndex() == 1)
	{
		for (const auto& object : SceneManager::GetInstance().GetScene(1).GetAllObjects())
		{
			if (object->GetComponent<EnemyComponent>())
			{
				object->MarkForDelete();
			}
		}
	}
}