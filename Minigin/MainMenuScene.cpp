#include "MainMenuScene.h"
#include "InputManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "GoToMainSceneCommand.h"
#include "ChangeModeCommand.h"
#include "Scene.h"
using namespace dae;

MainMenuScene::MainMenuScene(std::shared_ptr<Scene> pScene) : m_MainMenuScene{ pScene }
{
	m_Gamemodes[0] = "Singeplayer - PvE";
	m_Gamemodes[1] = "Versus - PvP";
	m_Gamemodes[2] = "Coop";
}

void MainMenuScene::Load()
{
	auto& input = InputManager::GetInstance();
	auto pTronFont = ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);

	auto goMainMenuBG = std::make_shared<GameObject>(m_MainMenuScene.get());
	goMainMenuBG->AddComponent<TextureComponent>()->AddTexture("MainMenuBG.jpg");

	auto goStartText = std::make_shared<GameObject>(m_MainMenuScene.get());
	goStartText->AddComponent<TextComponent>()->SetText("A/ENTER to start the Game");
	goStartText->GetComponent<TextComponent>()->SetFont(pTronFont);
	goStartText->GetComponent<TextComponent>()->SetFontColor(0, 255, 0);
	goStartText->AddComponent<TransformComponent>()->SetPosition(100.f, 100.f, 0.f);

	auto goQuitText = std::make_shared<GameObject>(m_MainMenuScene.get());
	goQuitText->AddComponent<TextComponent>()->SetText("B/ESC to quit Application");
	goQuitText->GetComponent<TextComponent>()->SetFont(pTronFont);
	goQuitText->GetComponent<TextComponent>()->SetFontColor(255, 0, 0);
	goQuitText->AddComponent<TransformComponent>()->SetPosition(100.f, 250.f, 0.f);

	auto goChangeText = std::make_shared<GameObject>(m_MainMenuScene.get());
	goChangeText->AddComponent<TextComponent>()->SetText("Y/TAB to change GameMode");
	goChangeText->GetComponent<TextComponent>()->SetFont(pTronFont);
	goChangeText->GetComponent<TextComponent>()->SetFontColor(255, 255, 0);
	goChangeText->AddComponent<TransformComponent>()->SetPosition(100.f, 400.f, 0.f);

	auto goGamemodeText = std::make_shared<GameObject>(m_MainMenuScene.get());
	goGamemodeText->AddComponent<TextComponent>()->SetText("Gamemode: ");
	goGamemodeText->GetComponent<TextComponent>()->SetFont(pTronFont);
	goGamemodeText->GetComponent<TextComponent>()->SetFontColor(255, 255, 255);
	goGamemodeText->AddComponent<TransformComponent>()->SetPosition(50.f, 500.f, 0.f);

	auto goGamemode = std::make_shared<dae::GameObject>(m_MainMenuScene.get());
	goGamemode->AddComponent<dae::TextComponent>()->SetText(m_Gamemodes[0]);
	goGamemode->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goGamemode->GetComponent<dae::TextComponent>()->SetFontColor(255, 255, 255);
	goGamemode->AddComponent<dae::TransformComponent>()->SetPosition(250.f, 500.f, 0.f);

	auto goNextScene = std::make_shared<GameObject>(m_MainMenuScene.get());

	auto goToNextScene = std::make_unique<GoToMainSceneCommand>(goNextScene.get());
	auto goToNextSceneGP = std::make_unique<GoToMainSceneCommand>(goNextScene.get());
	auto goToNextSceneGP2 = std::make_unique<GoToMainSceneCommand>(goNextScene.get());

	auto changeModeCommand = std::make_unique<ChangeModeCommand>(goGamemode.get(), m_Gamemodes);
	auto changeModeCommandGP = std::make_unique<ChangeModeCommand>(goGamemode.get(), m_Gamemodes);
	auto changeModeCommandGP2 = std::make_unique<ChangeModeCommand>(goGamemode.get(), m_Gamemodes);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RETURN, std::move(goToNextScene), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_TAB, std::move(changeModeCommand), 1);

	auto p0 = std::make_unique<XBox360Controller>(0);
	auto p1 = std::make_unique<XBox360Controller>(1);

	input.AddController(std::move(p0));
	input.AddController(std::move(p1));

	input.BindCommandController(0, XBox360Controller::ControllerButton::Y, std::move(changeModeCommandGP), 1);
	input.BindCommandController(0, XBox360Controller::ControllerButton::A, std::move(goToNextSceneGP), 1);

	input.BindCommandController(1, XBox360Controller::ControllerButton::Y, std::move(changeModeCommandGP2), 1);
	input.BindCommandController(1, XBox360Controller::ControllerButton::A, std::move(goToNextSceneGP2), 1);

	goMainMenuBG->AddGameObject();
	goStartText->AddGameObject();
	goQuitText->AddGameObject();
	goChangeText->AddGameObject();
	goNextScene->AddGameObject();
	goGamemodeText->AddGameObject();
	goGamemode->AddGameObject();

	m_MainMenuScene->Start();
}
