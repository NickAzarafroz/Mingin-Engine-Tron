#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "InputManager.h"

#include "TransformComponent.h"
#include "TextureComponent.h"
#include "FPSComponent.h"
#include "RotateComponent.h"
#include "LiveDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "GridComponent.h"
#include "BoxTriggerComponent.h"
#include "AIComponent.h"
#include "PlayerComponent.h"

#include "MoveCommand.h"
#include "MoveGridCommand.h"
#include "MoveTurretCommand.h"
#include "SpawnBulletCommand.h"

#include "XBox360Controller.h"

void load()
{
	dae::SceneManager::GetInstance().CreateScene("Menu");
	dae::SceneManager::GetInstance().CreateScene("MainGame");
	dae::SceneManager::GetInstance().Initialize();
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

    return 0;
}