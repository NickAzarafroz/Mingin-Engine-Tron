#include "AliveComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"
#include "TextureComponent.h"
#include "MoveGridCommand.h"
#include "ChangeModeCommand.h"
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
			MoveGridCommandP2::m_MovementFlag = false;
			SceneManager::GetInstance().LoadLevel2();
			break;
		case 1:
			MoveGridCommand::m_MovementFlag = false;
			MoveGridCommandP2::m_MovementFlag = false;
			SceneManager::GetInstance().LoadLevel3();
			break;
		case 2:
			MoveGridCommand::m_MovementFlag = false;
			MoveGridCommandP2::m_MovementFlag = false;
			SceneManager::GetInstance().LoadLevel1();
			break;
		default:
			break;
		}
	}

	if(m_PlayerCondition)
	{
		for (const auto& object : SceneManager::GetInstance().GetScene(1).GetAllObjects())
		{
			if (object->GetComponent<PlayerComponent>())
			{
				m_CurrentScore = object->GetComponent<PlayerComponent>()->GetScore();
				return;
			}
		}

		SceneManager::GetInstance().LoadEndScene(m_CurrentScore);
		SceneManager::GetInstance().GoNextScene();
	}

	if(m_OnePlayerCondition)
	{
		int currentPlayers{};

		for (const auto& object : SceneManager::GetInstance().GetScene(1).GetAllObjects())
		{
			if (object->GetComponent<PlayerComponent>())
			{
				++currentPlayers;
				m_CurrentScore = m_pPlayers[0]->GetComponent<PlayerComponent>()->GetScore();
			}
		}

		if (currentPlayers < 2) 
		{
			if(ChangeModeCommand::m_ModeIndex == 1)
			{
				SceneManager::GetInstance().LoadEndScene();
				SceneManager::GetInstance().GoNextScene();
			}
			else
			{
				SceneManager::GetInstance().LoadEndScene(m_CurrentScore);
				SceneManager::GetInstance().GoNextScene();
			}
		}
	}
}

void AliveComponent::CheckIfEnemiesAlive(bool condition)
{
	m_EnemiesCondition = condition;
}

void AliveComponent::CheckIfPlayerAlive(bool condition)
{
	m_PlayerCondition = condition;
}

void AliveComponent::CheckIfOnePlayerAlive(bool condition)
{
	m_OnePlayerCondition = condition;
}

void AliveComponent::AddPlayersToCheck(std::shared_ptr<GameObject> pPlayer)
{
	m_pPlayers.emplace_back(pPlayer);
}