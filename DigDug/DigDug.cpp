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
//#include "LiveDisplayComponent.h"
//#include "ScoreDisplayComponent.h"
#include "GridComponent.h"

#include "AllCommands.h"
#include "XBox360Controller.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();

	auto pDigDugFont = dae::ResourceManager::GetInstance().LoadFont("DigDug_Font.ttf", 14);
	auto pFontFpsText = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	auto goBackground = std::make_shared<dae::GameObject>();
	auto goLogo = std::make_shared<dae::GameObject>();
	auto goHighScoreText = std::make_shared<dae::GameObject>();
	auto goRoundText = std::make_shared<dae::GameObject>();
	auto goPlayer1Text = std::make_shared<dae::GameObject>();
	auto goFPS = std::make_shared<dae::GameObject>();
	auto goPlayer = std::make_shared<dae::GameObject>();
	auto goEnemy = std::make_shared<dae::GameObject>();
	auto goGrid = std::make_shared<dae::GameObject>();

	auto p0 = std::make_unique<dae::XBox360Controller>(0);

	/*auto moveRightCommand = std::make_unique<dae::MoveCommand>(goPlayer.get(), 50.f, glm::vec2{ 1.f, 0.f });
	auto moveLeftCommand = std::make_unique<dae::MoveCommand>(goPlayer.get(), 50.f, glm::vec2{ -1.f, 0.f });
	auto moveUpCommand = std::make_unique<dae::MoveCommand>(goPlayer.get(), 50.f, glm::vec2{ 0.f, -1.f });
	auto moveDownCommand = std::make_unique<dae::MoveCommand>(goPlayer.get(), 50.f, glm::vec2{ 0.f, 1.f });*/

	//input.AddController(std::move(p0));

	/*input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadRight, std::move(moveRightCommand));
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadLeft, std::move(moveLeftCommand));
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadUp, std::move(moveUpCommand));
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadDown, std::move(moveDownCommand));*/

	//Background Texture Top
	//-----------------------------------------------------------------------
	goBackground->AddComponent<dae::TextureComponent>()->SetTexture("DigDugBG.png");
	//--------------------------------------------------------------------------

	//Logo Texture
	//-----------------------------------------------------------------------
	//goLogo->AddComponent<dae::TextureComponent>()->SetTexture("logo.tga");
	//goLogo->SetLocalPosition(glm::vec3(216.f, 180.f, 0.f));
	//--------------------------------------------------------------------------

	//HighScore Text
	//--------------------------------------------------------------------------
	goHighScoreText->AddComponent<dae::TextComponent>()->SetText("HIGH SCORE");
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFont(pDigDugFont);
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goHighScoreText->SetLocalPosition(glm::vec3(140.f, 30.f, 0.f));
	//--------------------------------------------------------------------------

	//Round Text
	//--------------------------------------------------------------------------
	goRoundText->AddComponent<dae::TextComponent>()->SetText("ROUND");
	goRoundText->GetComponent<dae::TextComponent>()->SetFont(pDigDugFont);
	goRoundText->GetComponent<dae::TextComponent>()->SetFontColor(255, 255, 255);
	goRoundText->SetLocalPosition(glm::vec3(360.f, 520.f, 0.f));
	//--------------------------------------------------------------------------

	//Player 1 Text
	//--------------------------------------------------------------------------
	goPlayer1Text->AddComponent<dae::TextComponent>()->SetText("P1");
	goPlayer1Text->GetComponent<dae::TextComponent>()->SetFont(pDigDugFont);
	goPlayer1Text->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goPlayer1Text->SetLocalPosition(glm::vec3(60.f, 30.f, 0.f));
	//--------------------------------------------------------------------------

	//FPS
	//--------------------------------------------------------------------------
	goFPS->AddComponent<dae::FPSComponent>();
	goFPS->AddComponent<dae::TextComponent>();
	goFPS->GetComponent<dae::TextComponent>()->SetFont(pDigDugFont);
	goFPS->GetComponent<dae::TextComponent>()->SetFontColor(0, 255, 0);
	goFPS->SetLocalPosition(glm::vec3(5.f, 5.f, 0.f));
	//--------------------------------------------------------------------------

	//Player
	//--------------------------------------------------------------------------
	goPlayer->AddComponent<dae::TextureComponent>()->SetTexture("DigDugPlayer.png");
	goPlayer->SetLocalPosition(glm::vec3(32.f, 32.f, 0.0f));
	//---------------------------------------------------------------------------

	//Enemy
	//---------------------------------------------------------------------------
	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("DigDugEnemy.png");
	goEnemy->SetLocalPosition(glm::vec3(320.f, 270.f, 0.0f));
	//---------------------------------------------------------------------------

	//Grid
	//---------------------------------------------------------------------------
	goGrid->AddComponent<dae::GridComponent>();
	goGrid->AddComponent<dae::TextureComponent>()->SetTexture("Grid[x].png");
	goGrid->GetComponent<dae::GridComponent>()->Initialize(32.f, 32.f);
	//---------------------------------------------------------------------------

	auto gridRight = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridLeft = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridUp = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridDown = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_D, std::move(gridRight));
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_A, std::move(gridLeft));
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_S, std::move(gridDown));
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_W, std::move(gridUp));


	scene.Add(goBackground);
	//scene.Add(goLogo);
	scene.Add(goHighScoreText);
	scene.Add(goRoundText);
	scene.Add(goPlayer1Text);
	scene.Add(goFPS);
	scene.Add(goPlayer);
	scene.Add(goEnemy);
	scene.Add(goGrid);
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);

    return 0;
}