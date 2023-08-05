#include "MainMenuScene.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "GoToNextSceneCommand.h"
#include "Scene.h"
using namespace dae;

MainMenuScene::MainMenuScene(std::shared_ptr<Scene> pScene) : m_MainMenuScene{ pScene }
{

}

void MainMenuScene::Load()
{
	auto& input = dae::InputManager::GetInstance();
	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);

	auto goMainMenuBG = std::make_shared<dae::GameObject>(m_MainMenuScene.get());
	goMainMenuBG->AddComponent<dae::TextureComponent>()->AddTexture("MainMenuBG.jpg");

	auto goStartText = std::make_shared<dae::GameObject>(m_MainMenuScene.get());
	goStartText->AddComponent<dae::TextComponent>()->SetText("A/SPACE to start the Game");
	goStartText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goStartText->GetComponent<dae::TextComponent>()->SetFontColor(0, 255, 0);

	goStartText->AddComponent<dae::TransformComponent>()->SetPosition(100.f, 100.f, 0.f);

	auto goQuitText = std::make_shared<dae::GameObject>(m_MainMenuScene.get());
	goQuitText->AddComponent<dae::TextComponent>()->SetText("B/ESC to quit Application");
	goQuitText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goQuitText->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);

	goQuitText->AddComponent<dae::TransformComponent>()->SetPosition(100.f, 250.f, 0.f);

	auto goChangeText = std::make_shared<dae::GameObject>(m_MainMenuScene.get());
	goChangeText->AddComponent<dae::TextComponent>()->SetText("Y/TAB to change GameMode");
	goChangeText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goChangeText->GetComponent<dae::TextComponent>()->SetFontColor(255, 255, 0);

	goChangeText->AddComponent<dae::TransformComponent>()->SetPosition(100.f, 400.f, 0.f);

	auto goNextScene = std::make_shared<dae::GameObject>(m_MainMenuScene.get());

	auto goToNextScene = std::make_unique<dae::GoToNextSceneCommand>(goNextScene.get());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RETURN, std::move(goToNextScene), 1);

	goMainMenuBG->AddGameObject();
	goStartText->AddGameObject();
	goQuitText->AddGameObject();
	goChangeText->AddGameObject();
	goNextScene->AddGameObject();

	m_MainMenuScene->Start();
}
