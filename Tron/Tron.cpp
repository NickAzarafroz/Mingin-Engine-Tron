#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "Scene.h"

void load()
{
	dae::SceneManager::GetInstance().CreateScene("Menu");
	dae::SceneManager::GetInstance().CreateScene("MainGame");
	dae::SceneManager::GetInstance().CreateScene("EndScreen");
	dae::SceneManager::GetInstance().Initialize();
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

    return 0;
}