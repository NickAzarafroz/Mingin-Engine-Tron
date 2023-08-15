#include "AliveComponent.h"
#include "EnemyComponent.h"
#include "MoveGridCommand.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace dae;

void AliveComponent::Update(float)
{
	if(m_EnemiesCondition)
	{
		int scene = SceneManager::GetInstance().GetLevel();

		for (const auto& object : SceneManager::GetInstance().GetScene(1).GetAllObjects())
		{
			if (object->GetComponent<EnemyComponent>())
			{
				return;
			}
		}

		switch (scene)
		{
		case 0: 
			MoveGridCommand::m_MovementFlag = false;
			SceneManager::GetInstance().LoadLevel2();
			break;
		case 1:
			MoveGridCommand::m_MovementFlag = false;
			SceneManager::GetInstance().LoadLevel3();
			break;
		case 2:
			MoveGridCommand::m_MovementFlag = false;
			SceneManager::GetInstance().LoadLevel1();
			break;
		default:
			break;
		}
	}
}

void AliveComponent::CheckIfEnemiesAlive(bool condition)
{
	m_EnemiesCondition = condition;
}
