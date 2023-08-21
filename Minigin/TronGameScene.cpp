#include "TronGameScene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "GridComponent.h"
#include "BoxTriggerComponent.h"
#include "PlayerComponent.h"
#include "EnemyComponent.h"
#include "ScoreDisplayComponent.h"
#include "LiveDisplayComponent.h"
#include "AIComponent.h"
#include "MoveGridCommand.h"
#include "SpawnBulletCommand.h"
#include "MoveTurretCommand.h"
#include "ValidCellComponent.h"
#include "AliveComponent.h"
#include "SkipLevelCommand.h"
#include "ServiceLocator.h"
#include "Scene.h"
using namespace dae;

TronGameScene::TronGameScene(std::shared_ptr<Scene> pScene) : m_TronGameScene{ pScene } {}

void TronGameScene::LoadSinglePlayer()
{
	auto& input = dae::InputManager::GetInstance();
	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);
	auto pFontFpsText = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto& soundsystem = dae::ServiceLocator::GetSoundSystem();

	auto goHighScoreText = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHighScoreValue = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer1Text = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goFPS = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goGrid = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthText = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealth = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayerTurret = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayerAlive = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	goPlayerAlive->AddComponent<dae::AliveComponent>()->CheckIfPlayerAlive(true);

	//Player 1 Text
	//--------------------------------------------------------------------------
	goPlayer1Text->AddComponent<dae::TextComponent>()->SetText("P1:");
	goPlayer1Text->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goPlayer1Text->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goPlayer1Text->AddComponent<dae::TransformComponent>()->SetPosition(400.f, 30.f, 0.f);
	//--------------------------------------------------------------------------

	//FPS
	//--------------------------------------------------------------------------
	goFPS->AddComponent<dae::FPSComponent>();
	goFPS->AddComponent<dae::TextComponent>();
	goFPS->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goFPS->GetComponent<dae::TextComponent>()->SetFontColor(0, 255, 0);
	goFPS->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 5.f, 0.f);
	//--------------------------------------------------------------------------

	//Grid
	//---------------------------------------------------------------------------
	goGrid->AddComponent<dae::TextureComponent>();
	goGrid->GetComponent<dae::TextureComponent>()->AddTexture("path.png");
	goGrid->GetComponent<dae::TextureComponent>()->AddTexture("wall.png");

	goGrid->AddComponent<dae::GridComponent>();
	goGrid->GetComponent<dae::GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron.json");
	//---------------------------------------------------------------------------

	//Player
	//--------------------------------------------------------------------------
	goPlayer->AddComponent<dae::TextureComponent>()->SetTexture("RedTank.png");
	goPlayer->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goPlayer->AddComponent<dae::PlayerComponent>()->SetName("Player1");
	goPlayer->AddComponent<dae::AliveComponent>()->CheckIfEnemiesAlive(true);
	goPlayer->AddComponent<dae::TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
	//---------------------------------------------------------------------------

	//HighScore Text
	//--------------------------------------------------------------------------
	goHighScoreText->AddComponent<dae::TextComponent>()->SetText("HIGH SCORE");
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goHighScoreText->AddComponent<dae::TransformComponent>()->SetPosition(450.f, 30.f, 0.f);

	goHighScoreValue->AddComponent<dae::TextComponent>()->SetText("0");
	goHighScoreValue->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHighScoreValue->GetComponent<dae::TextComponent>()->SetFontColor(0, 0, 255);
	goHighScoreValue->AddComponent<dae::ScoreDisplayComponent>()->SetObjectToDisplayScore(goPlayer.get());
	goHighScoreValue->AddComponent<dae::TransformComponent>()->SetPosition(515.f, 60.f, 0.f);
	//--------------------------------------------------------------------------

	//Enemy
	//---------------------------------------------------------------------------
	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(288.f, 320.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(384.f, 352.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy3->AddComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer);
	goEnemy3->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(192.f, 192.f, 0.0f);

	std::vector<std::shared_ptr<dae::GameObject>> goEnemies;
	goEnemies.emplace_back(goEnemy);
	goEnemies.emplace_back(goEnemy2);
	goEnemies.emplace_back(goEnemy3);

	m_pEnemiesLv1 = goEnemies;
	//---------------------------------------------------------------------------

	//Health Displayer
	//---------------------------------------------------------------------------
	goHealthText->AddComponent<dae::TextComponent>()->SetText("HealthPoints:");
	goHealthText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthText->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 255);
	goHealthText->AddComponent<dae::TransformComponent>()->SetPosition(0.f, 50.f, 0.f);

	goHealth->AddComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealth->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 255);
	goHealth->AddComponent<dae::LiveDisplayComponent>()->SetObjectToDisplayLives(goPlayer.get());
	goHealth->AddComponent<dae::TransformComponent>()->SetPosition(250.f, 50.f, 0.f);
	//---------------------------------------------------------------------------

	//Player Turret
	//-----------------------------------------------------------------------------------
	goPlayerTurret->AddComponent<dae::TextureComponent>()->AddTexture("RedTankGun.png");
	goPlayerTurret->AddComponent<dae::TransformComponent>()->SetPosition(24.f, 120.f, 0.f);
	//-----------------------------------------------------------------------------------

	auto gridRight = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridLeft = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridUp = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridDown = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	auto incTurret = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), true);
	auto decTurret = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), false);

	auto incTurretGP = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), true);
	auto decTurretGP = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), false);

	auto spawnBullet = std::make_unique<dae::SpawnBulletCommand>(goPlayer.get(), goEnemies, goGrid->GetComponent<dae::GridComponent>());
	auto spawnBulletGP = std::make_unique<dae::SpawnBulletCommand>(goPlayer.get(), goEnemies, goGrid->GetComponent<dae::GridComponent>());

	auto skipLevel = std::make_unique<dae::SkipLevelCommand>(goPlayer.get());
	auto skipLevelGP = std::make_unique<dae::SkipLevelCommand>(goPlayer.get());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_D, std::move(gridRight), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_A, std::move(gridLeft), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_S, std::move(gridDown), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_W, std::move(gridUp), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBullet), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_UP, std::move(incTurret), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_DOWN, std::move(decTurret), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_F1, std::move(skipLevel), 1);

	auto moveRightCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveLeftCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveUpCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveDownCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadRight, std::move(moveRightCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadLeft, std::move(moveLeftCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadUp, std::move(moveUpCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadDown, std::move(moveDownCommand), 0);

	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletGP), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::RightShoulder, std::move(incTurretGP), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::LeftShoulder, std::move(decTurretGP), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::Start, std::move(skipLevelGP), 1);

	goPlayer->SendMessageID(0);

	goPlayerTurret->SetParent(goPlayer.get(), true);

	m_pPlayer = goPlayer;
	m_pGrid = goGrid;

	goPlayerAlive->AddGameObject();
	goGrid->AddGameObject();
	goHighScoreText->AddGameObject();
	goHighScoreValue->AddGameObject();
	goPlayer1Text->AddGameObject();
	goFPS->AddGameObject();
	goPlayer->AddGameObject();
	goHealthText->AddGameObject();
	goHealth->AddGameObject();
	goEnemy->AddGameObject();
	goEnemy2->AddGameObject();
	goEnemy3->AddGameObject();

	soundsystem.Play("../Data/Background.mp3", 20.f, -1);

	m_TronGameScene->Start();
}

void TronGameScene::LoadVersus()
{
	auto& input = dae::InputManager::GetInstance();

	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);
	auto pFontFpsText = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto& soundsystem = dae::ServiceLocator::GetSoundSystem();

	auto goFPS = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goGrid = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthText = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthTextP2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealth = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthP2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayerTurret = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayerTurret2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayersAlive = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	//FPS
	//--------------------------------------------------------------------------
	goFPS->AddComponent<dae::FPSComponent>();
	goFPS->AddComponent<dae::TextComponent>();
	goFPS->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goFPS->GetComponent<dae::TextComponent>()->SetFontColor(0, 255, 0);

	goFPS->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 5.f, 0.f);
	//--------------------------------------------------------------------------

	//Grid
	//---------------------------------------------------------------------------
	goGrid->AddComponent<dae::TextureComponent>();
	goGrid->GetComponent<dae::TextureComponent>()->AddTexture("path.png");
	goGrid->GetComponent<dae::TextureComponent>()->AddTexture("wall.png");

	goGrid->AddComponent<dae::GridComponent>();
	goGrid->GetComponent<dae::GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron.json");
	//---------------------------------------------------------------------------

	//Player 1
	//--------------------------------------------------------------------------
	goPlayer->AddComponent<dae::TextureComponent>()->SetTexture("RedTank.png");
	goPlayer->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goPlayer->AddComponent<dae::PlayerComponent>()->SetName("Player1");
	goPlayer->AddComponent<dae::TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
	//---------------------------------------------------------------------------

	//Player 2
	//--------------------------------------------------------------------------
	goPlayer2->AddComponent<dae::TextureComponent>()->SetTexture("PinkTank.png");
	goPlayer2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goPlayer2->AddComponent<dae::PlayerComponent>()->SetName("Player2");
	goPlayer2->AddComponent<dae::TransformComponent>()->SetPosition(576.f, 480.f, 0.0f);
	//---------------------------------------------------------------------------

	goPlayersAlive->AddComponent<dae::AliveComponent>()->AddPlayersToCheck(goPlayer);
	goPlayersAlive->GetComponent<dae::AliveComponent>()->AddPlayersToCheck(goPlayer2);
	goPlayersAlive->GetComponent<dae::AliveComponent>()->CheckIfOnePlayerAlive(true);

	std::vector<std::shared_ptr<dae::GameObject>> goOtherPlayers2;
	goOtherPlayers2.emplace_back(goPlayer2);

	std::vector<std::shared_ptr<dae::GameObject>> goOtherPlayers1;
	goOtherPlayers1.emplace_back(goPlayer);

	//Health Displayer
	//---------------------------------------------------------------------------
	goHealthText->AddComponent<dae::TextComponent>()->SetText("HealthPoints P1:");
	goHealthText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthText->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goHealthText->AddComponent<dae::TransformComponent>()->SetPosition(0.f, 40.f, 0.f);

	goHealthTextP2->AddComponent<dae::TextComponent>()->SetText("HealthPoints P2:");
	goHealthTextP2->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthTextP2->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 255);
	goHealthTextP2->AddComponent<dae::TransformComponent>()->SetPosition(0.f, 70.f, 0.f);

	goHealth->AddComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealth->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goHealth->AddComponent<dae::LiveDisplayComponent>()->SetObjectToDisplayLives(goPlayer.get());
	goHealth->AddComponent<dae::TransformComponent>()->SetPosition(300.f, 40.f, 0.f);

	goHealthP2->AddComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthP2->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 255);
	goHealthP2->AddComponent<dae::LiveDisplayComponent>()->SetObjectToDisplayLives(goPlayer2.get());
	goHealthP2->AddComponent<dae::TransformComponent>()->SetPosition(310.f, 70.f, 0.f);
	//---------------------------------------------------------------------------

	//Player Turret
	//-----------------------------------------------------------------------------------
	goPlayerTurret->AddComponent<dae::TextureComponent>()->AddTexture("RedTankGun.png");
	goPlayerTurret->AddComponent<dae::TransformComponent>()->SetPosition(24.f, 120.f, 0.f);
	//-----------------------------------------------------------------------------------

	//Player2 Turret
	//-----------------------------------------------------------------------------------
	goPlayerTurret2->AddComponent<dae::TextureComponent>()->AddTexture("BlueTankGun.png");
	goPlayerTurret2->AddComponent<dae::TransformComponent>()->SetPosition(568.f, 472.f, 0.f);
	//-----------------------------------------------------------------------------------

	auto gridRight = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridLeft = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridUp = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridDown = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	auto gridRight2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridLeft2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridUp2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridDown2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	auto incTurret = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), true);
	auto decTurret = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), false);
	auto incTurret2 = std::make_unique<dae::MoveTurretCommandP2>(goPlayerTurret2.get(), true);
	auto decTurret2 = std::make_unique<dae::MoveTurretCommandP2>(goPlayerTurret2.get(), false);
	auto incTurretGP = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), true);
	auto decTurretGP = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), false);
	auto incTurretGP2 = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret2.get(), true);
	auto decTurretGP2 = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret2.get(), false);

	auto spawnBulletP1 = std::make_unique<dae::SpawnBulletCommand>(goPlayer.get(), goOtherPlayers2, goGrid->GetComponent<dae::GridComponent>());
	auto spawnBulletP1GP = std::make_unique<dae::SpawnBulletCommand>(goPlayer.get(), goOtherPlayers2, goGrid->GetComponent<dae::GridComponent>());
	auto spawnBulletP2 = std::make_unique<dae::SpawnBulletCommand>(goPlayer2.get(), goOtherPlayers1, goGrid->GetComponent<dae::GridComponent>());
	auto spawnBulletP2GP = std::make_unique<dae::SpawnBulletCommand>(goPlayer2.get(), goOtherPlayers1, goGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_D, std::move(gridRight), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_A, std::move(gridLeft), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_S, std::move(gridDown), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_W, std::move(gridUp), 0);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_R, std::move(incTurret), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_F, std::move(decTurret), 1);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RIGHT, std::move(gridRight2), 2);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_LEFT, std::move(gridLeft2), 2);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_DOWN, std::move(gridDown2), 2);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_UP, std::move(gridUp2), 2);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_P, std::move(incTurret2), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_L, std::move(decTurret2), 1);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBulletP1), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RSHIFT, std::move(spawnBulletP2), 1);

	auto moveRightCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveLeftCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveUpCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveDownCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	auto moveRightCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{1.f, 0.f}, goGrid->GetComponent<dae::GridComponent>());
	auto moveLeftCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveUpCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveDownCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadRight, std::move(moveRightCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadLeft, std::move(moveLeftCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadUp, std::move(moveUpCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadDown, std::move(moveDownCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletP1GP), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::RightShoulder, std::move(incTurretGP), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::LeftShoulder, std::move(decTurretGP), 1);

	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadRight, std::move(moveRightCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadLeft, std::move(moveLeftCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadUp, std::move(moveUpCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadDown, std::move(moveDownCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletP2GP), 1);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::RightShoulder, std::move(incTurretGP2), 1);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::LeftShoulder, std::move(decTurretGP2), 1);

	goPlayer->SendMessageID(0);

	goPlayerTurret->SetParent(goPlayer.get(), true);
	goPlayerTurret2->SetParent(goPlayer2.get(), true);

	m_pPlayer = goPlayer;
	m_pGrid = goGrid;

	goPlayersAlive->AddGameObject();
	goGrid->AddGameObject();
	goFPS->AddGameObject();
	goPlayer->AddGameObject();
	goPlayer2->AddGameObject();
	goHealthText->AddGameObject();
	goHealthTextP2->AddGameObject();
	goHealth->AddGameObject();
	goHealthP2->AddGameObject();

	soundsystem.Play("../Data/Background.mp3", 20.f, -1);

	m_TronGameScene->Start();
}

void TronGameScene::LoadCoop()
{
	auto& input = dae::InputManager::GetInstance();

	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);
	auto pFontFpsText = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	auto& soundsystem = dae::ServiceLocator::GetSoundSystem();

	auto goHighScoreText = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHighScoreValue = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goFPS = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goGrid = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthTextP1 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthTextP2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthP1 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealthP2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayerTurret = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayerTurret2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayersAlive = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	//FPS
	//--------------------------------------------------------------------------
	goFPS->AddComponent<dae::FPSComponent>();
	goFPS->AddComponent<dae::TextComponent>();
	goFPS->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goFPS->GetComponent<dae::TextComponent>()->SetFontColor(0, 255, 0);
	goFPS->AddComponent<dae::TransformComponent>()->SetPosition(5.f, 5.f, 0.f);
	//--------------------------------------------------------------------------

	//Grid
	//---------------------------------------------------------------------------
	goGrid->AddComponent<dae::TextureComponent>();
	goGrid->GetComponent<dae::TextureComponent>()->AddTexture("path.png");
	goGrid->GetComponent<dae::TextureComponent>()->AddTexture("wall.png");

	goGrid->AddComponent<dae::GridComponent>();
	goGrid->GetComponent<dae::GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron.json");
	//---------------------------------------------------------------------------

	//Player
	//--------------------------------------------------------------------------
	goPlayer->AddComponent<dae::TextureComponent>()->SetTexture("RedTank.png");
	goPlayer->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goPlayer->AddComponent<dae::PlayerComponent>()->SetName("Player1");
	goPlayer->AddComponent<dae::AliveComponent>()->CheckIfEnemiesAlive(true);
	goPlayer->AddComponent<dae::TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
	//---------------------------------------------------------------------------

	//Player 2
	//--------------------------------------------------------------------------
	goPlayer2->AddComponent<dae::TextureComponent>()->SetTexture("PinkTank.png");
	goPlayer2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goPlayer2->AddComponent<dae::PlayerComponent>()->SetName("Player2");
	goPlayer2->AddComponent<dae::TransformComponent>()->SetPosition(576.f, 480.f, 0.0f);
	//---------------------------------------------------------------------------

	goPlayersAlive->AddComponent<dae::AliveComponent>()->AddPlayersToCheck(goPlayer);
	goPlayersAlive->GetComponent<dae::AliveComponent>()->AddPlayersToCheck(goPlayer2);
	goPlayersAlive->GetComponent<dae::AliveComponent>()->CheckIfOnePlayerAlive(true);

	//HighScore Text
	//--------------------------------------------------------------------------
	goHighScoreText->AddComponent<dae::TextComponent>()->SetText("SCORE P1 P2:");
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goHighScoreText->AddComponent<dae::TransformComponent>()->SetPosition(350.f, 30.f, 0.f);

	goHighScoreValue->AddComponent<dae::TextComponent>()->SetText("0");
	goHighScoreValue->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHighScoreValue->GetComponent<dae::TextComponent>()->SetFontColor(0, 0, 255);
	goHighScoreValue->AddComponent<dae::ScoreDisplayComponent>()->SetObjectToDisplayScore(goPlayer.get());
	goHighScoreValue->AddComponent<dae::TransformComponent>()->SetPosition(450.f, 60.f, 0.f);
	//--------------------------------------------------------------------------

	//Health Displayer
	//---------------------------------------------------------------------------
	goHealthTextP1->AddComponent<dae::TextComponent>()->SetText("HealthPoints P1: ");
	goHealthTextP1->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthTextP1->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goHealthTextP1->AddComponent<dae::TransformComponent>()->SetPosition(0.f, 30.f, 0.f);

	goHealthTextP2->AddComponent<dae::TextComponent>()->SetText("HealthPoints P2: ");
	goHealthTextP2->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthTextP2->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 255);
	goHealthTextP2->AddComponent<dae::TransformComponent>()->SetPosition(0.f, 60.f, 0.f);

	goHealthP1->AddComponent<dae::TextComponent>()->SetText("3");
	goHealthP1->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthP1->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 0);
	goHealthP1->AddComponent<dae::LiveDisplayComponent>()->SetObjectToDisplayLives(goPlayer.get());
	goHealthP1->AddComponent<dae::TransformComponent>()->SetPosition(310.f, 30.f, 0.f);

	goHealthP2->AddComponent<dae::TextComponent>()->SetText("3");
	goHealthP2->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealthP2->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 255);
	goHealthP2->AddComponent<dae::LiveDisplayComponent>()->SetObjectToDisplayLives(goPlayer2.get());
	goHealthP2->AddComponent<dae::TransformComponent>()->SetPosition(310.f, 60.f, 0.f);
	//---------------------------------------------------------------------------

	//Player Turret
	//-----------------------------------------------------------------------------------
	goPlayerTurret->AddComponent<dae::TextureComponent>()->AddTexture("RedTankGun.png");
	goPlayerTurret->AddComponent<dae::TransformComponent>()->SetPosition(24.f, 120.f, 0.f);
	//-----------------------------------------------------------------------------------

	//Player2 Turret
	//-----------------------------------------------------------------------------------
	goPlayerTurret2->AddComponent<dae::TextureComponent>()->AddTexture("BlueTankGun.png");
	goPlayerTurret2->AddComponent<dae::TransformComponent>()->SetPosition(568.f, 472.f, 0.f);
	//-----------------------------------------------------------------------------------

	//Enemy
	//---------------------------------------------------------------------------
	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer);
	goEnemy->GetComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer2);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(288.f, 320.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer);
	goEnemy2->GetComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer2);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(384.f, 352.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy3->AddComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer);
	goEnemy3->GetComponent<dae::AIComponent>()->AddObjectToShoot(goPlayer2);
	goEnemy3->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(192.f, 192.f, 0.0f);

	std::vector<std::shared_ptr<dae::GameObject>> goEnemies;
	goEnemies.emplace_back(goEnemy);
	goEnemies.emplace_back(goEnemy2);
	goEnemies.emplace_back(goEnemy3);

	m_pEnemiesLv1 = goEnemies;
	//---------------------------------------------------------------------------

	auto gridRight = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridLeft = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridUp = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridDown = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	auto gridRight2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridLeft2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridUp2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto gridDown2 = std::make_unique<dae::MoveGridCommandP2>(goPlayer2.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	auto incTurret = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), true);
	auto decTurret = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), false);
	auto incTurret2 = std::make_unique<dae::MoveTurretCommandP2>(goPlayerTurret2.get(), true);
	auto decTurret2 = std::make_unique<dae::MoveTurretCommandP2>(goPlayerTurret2.get(), false);
	auto incTurretGP = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), true);
	auto decTurretGP = std::make_unique<dae::MoveTurretCommand>(goPlayerTurret.get(), false);
	auto incTurret2GP = std::make_unique<dae::MoveTurretCommandP2>(goPlayerTurret2.get(), true);
	auto decTurret2GP = std::make_unique<dae::MoveTurretCommandP2>(goPlayerTurret2.get(), false);

	auto spawnBulletP1 = std::make_unique<dae::SpawnBulletCommand>(goPlayer.get(), goEnemies, goGrid->GetComponent<dae::GridComponent>());
	auto spawnBulletP1GP = std::make_unique<dae::SpawnBulletCommand>(goPlayer.get(), goEnemies, goGrid->GetComponent<dae::GridComponent>());
	auto spawnBulletP2 = std::make_unique<dae::SpawnBulletCommand>(goPlayer2.get(), goEnemies, goGrid->GetComponent<dae::GridComponent>());
	auto spawnBulletP2GP = std::make_unique<dae::SpawnBulletCommand>(goPlayer2.get(), goEnemies, goGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_D, std::move(gridRight), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_A, std::move(gridLeft), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_S, std::move(gridDown), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_W, std::move(gridUp), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_R, std::move(incTurret), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_F, std::move(decTurret), 1);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RIGHT, std::move(gridRight2), 2);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_LEFT, std::move(gridLeft2), 2);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_DOWN, std::move(gridDown2), 2);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_UP, std::move(gridUp2), 2);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_P, std::move(incTurret2), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_L, std::move(decTurret2), 1);

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBulletP1), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RSHIFT, std::move(spawnBulletP2), 1);

	auto moveRightCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveLeftCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveUpCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveDownCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	auto moveRightCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveLeftCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveUpCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveDownCommandP2 = std::make_unique<dae::MoveGridCommand>(goPlayer2.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadRight, std::move(moveRightCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadLeft, std::move(moveLeftCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadUp, std::move(moveUpCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadDown, std::move(moveDownCommand), 0);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletP1GP), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::RightShoulder, std::move(incTurretGP), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::LeftShoulder, std::move(decTurretGP), 1);

	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadRight, std::move(moveRightCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadLeft, std::move(moveLeftCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadUp, std::move(moveUpCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::DPadDown, std::move(moveDownCommandP2), 0);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletP2GP), 1);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::RightShoulder, std::move(incTurret2GP), 1);
	input.BindCommandController(1, dae::XBox360Controller::ControllerButton::LeftShoulder, std::move(decTurret2GP), 1);

	goPlayerTurret->SetParent(goPlayer.get(), true);
	goPlayerTurret2->SetParent(goPlayer2.get(), true);

	m_pPlayer = goPlayer;
	m_pPlayer2 = goPlayer2;
	m_pGrid = goGrid;

	goPlayersAlive->AddGameObject();
	goGrid->AddGameObject();
	goHighScoreText->AddGameObject();
	goHighScoreValue->AddGameObject();
	goFPS->AddGameObject();
	goPlayer->AddGameObject();
	goPlayer2->AddGameObject();
	goHealthTextP1->AddGameObject();
	goHealthTextP2->AddGameObject();
	goHealthP1->AddGameObject();
	goHealthP2->AddGameObject();
	goEnemy->AddGameObject();
	goEnemy2->AddGameObject();
	goEnemy3->AddGameObject();

	soundsystem.Play("../Data/Background.mp3", 20.f, -1);

	m_TronGameScene->Start();
}

void TronGameScene::ResetEnemies()
{
	switch (m_Level)
	{
	case 0:
		m_pEnemiesLv1[0]->GetComponent<TransformComponent>()->SetPosition(288.f, 320.f, 0.0f);
		m_pEnemiesLv1[0]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv1[1]->GetComponent<TransformComponent>()->SetPosition(384.f, 352.f, 0.0f);
		m_pEnemiesLv1[1]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv1[2]->GetComponent<TransformComponent>()->SetPosition(192.f, 192.f, 0.0f);
		m_pEnemiesLv1[2]->GetComponent<AIComponent>()->SetMovementFlag(false);
		break;
	case 1:
		m_pEnemiesLv2[0]->GetComponent<TransformComponent>()->SetPosition(384.f, 128.f, 0.0f);
		m_pEnemiesLv2[0]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv2[1]->GetComponent<TransformComponent>()->SetPosition(128.f, 384.f, 0.0f);
		m_pEnemiesLv2[1]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv2[2]->GetComponent<TransformComponent>()->SetPosition(544.f, 192.f, 0.0f);
		m_pEnemiesLv2[2]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv2[3]->GetComponent<TransformComponent>()->SetPosition(544.f, 448.f, 0.0f);
		m_pEnemiesLv2[3]->GetComponent<AIComponent>()->SetMovementFlag(false);
		break;
	case 2:
		m_pEnemiesLv3[0]->GetComponent<TransformComponent>()->SetPosition(224.f, 256.f, 0.0f);
		m_pEnemiesLv3[0]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv3[1]->GetComponent<TransformComponent>()->SetPosition(192.f, 416.f, 0.0f);
		m_pEnemiesLv3[1]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv3[2]->GetComponent<TransformComponent>()->SetPosition(416.f, 224.f, 0.0f);
		m_pEnemiesLv3[2]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv3[3]->GetComponent<TransformComponent>()->SetPosition(448.f, 416.f, 0.0f);
		m_pEnemiesLv3[3]->GetComponent<AIComponent>()->SetMovementFlag(false);
		m_pEnemiesLv3[4]->GetComponent<TransformComponent>()->SetPosition(192.f, 256.f, 0.0f);
		m_pEnemiesLv3[4]->GetComponent<AIComponent>()->SetMovementFlag(false);
		break;
	default:
		break;
	}

	for(const auto& object : m_TronGameScene->GetAllObjects())
	{
		if(object->GetComponent<ValidCellComponent>())
		{
			object->RemoveGameObject();
		}
	}
}

void TronGameScene::LoadLevel1()
{
	m_Level = 0;

	auto& input = dae::InputManager::GetInstance();

	m_pPlayer->GetComponent<TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
	if (m_pPlayer2) m_pPlayer2->GetComponent<TransformComponent>()->SetPosition(576.f, 480.f, 0.0f);
	m_pGrid->GetComponent<GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron.json");

	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(288.f, 320.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy2->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(384.f, 352.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy3->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy3->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy3->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(192.f, 192.f, 0.0f);

	std::vector<std::shared_ptr<dae::GameObject>> goEnemies;
	goEnemies.emplace_back(goEnemy);
	goEnemies.emplace_back(goEnemy2);
	goEnemies.emplace_back(goEnemy3);

	m_pEnemiesLv1 = goEnemies;

	auto spawnBulletP1 = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());
	if (m_pPlayer2)
	{
		auto spawnBulletP2 = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer2.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());
		input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RSHIFT, std::move(spawnBulletP2), 1);
	}
	auto spawnBulletGP = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBulletP1), 1);
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletGP), 1);

	goEnemy->AddGameObject();
	goEnemy2->AddGameObject();
	goEnemy3->AddGameObject();

	goEnemy->Start();
	goEnemy2->Start();
	goEnemy3->Start();
}

void TronGameScene::LoadLevel2()
{
	++m_Level;

	auto& input = dae::InputManager::GetInstance();

	m_pPlayer->GetComponent<TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
	if (m_pPlayer2) m_pPlayer2->GetComponent<TransformComponent>()->SetPosition(576.f, 480.f, 0.0f);
	m_pGrid->GetComponent<GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron2.json");

	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy4 = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(384.f, 128.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy2->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(128.f, 384.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer);
	if (m_pPlayer2) goEnemy3->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer2);
	goEnemy3->GetComponent<dae::BoxTriggerComponent>()->DestroyOtherAfterOverLap(true);
	goEnemy3->GetComponent<dae::BoxTriggerComponent>()->DecMyHealthAfterOverlap(true);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy3->GetComponent<dae::EnemyComponent>()->SetKillPoints(250);
	goEnemy3->AddComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy3->GetComponent<dae::AIComponent>()->SetSpeed(50.f);

	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(544.f, 192.f, 0.0f);

	goEnemy4->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy4->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy4->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer);
	if (m_pPlayer2) goEnemy4->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer2);
	goEnemy4->GetComponent<dae::BoxTriggerComponent>()->DestroyOtherAfterOverLap(true);
	goEnemy4->GetComponent<dae::BoxTriggerComponent>()->DecMyHealthAfterOverlap(true);
	goEnemy4->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy4->GetComponent<dae::EnemyComponent>()->SetKillPoints(250);
	goEnemy4->AddComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy4->GetComponent<dae::AIComponent>()->SetSpeed(50.f);

	goEnemy4->AddComponent<dae::TransformComponent>()->SetPosition(544.f, 448.f, 0.0f);

	std::vector<std::shared_ptr<dae::GameObject>> goEnemies;
	goEnemies.emplace_back(goEnemy);
	goEnemies.emplace_back(goEnemy2);
	goEnemies.emplace_back(goEnemy3);
	goEnemies.emplace_back(goEnemy4);

	m_pEnemiesLv2 = goEnemies;

	auto spawnBulletP1 = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());
	if (m_pPlayer2) 
	{
		auto spawnBulletP2 = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer2.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());
		input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RSHIFT, std::move(spawnBulletP2), 1);
	}
	auto spawnBulletGP = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBulletP1), 1);

	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletGP), 1);

	goEnemy->AddGameObject();
	goEnemy2->AddGameObject();
	goEnemy3->AddGameObject();
	goEnemy4->AddGameObject();

	goEnemy->Start();
	goEnemy2->Start();
	goEnemy3->Start();
	goEnemy4->Start();
}

void TronGameScene::LoadLevel3()
{
	++m_Level;

	auto& input = dae::InputManager::GetInstance();

	m_pPlayer->GetComponent<TransformComponent>()->SetPosition(32.f, 128.f, 0.0f);
	if (m_pPlayer2) m_pPlayer2->GetComponent<TransformComponent>()->SetPosition(576.f, 480.f, 0.0f);
	m_pGrid->GetComponent<GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron3.json");

	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy4 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy5 = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(224.f, 256.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy2->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(192.f, 416.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy3->AddComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer);
	if (m_pPlayer2) goEnemy3->GetComponent<dae::AIComponent>()->AddObjectToShoot(m_pPlayer2);
	goEnemy3->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(416.f, 224.f, 0.0f);

	goEnemy4->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy4->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy4->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer);
	if (m_pPlayer2) goEnemy4->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer2);
	goEnemy4->GetComponent<dae::BoxTriggerComponent>()->DestroyOtherAfterOverLap(true);
	goEnemy4->GetComponent<dae::BoxTriggerComponent>()->DecMyHealthAfterOverlap(true);
	goEnemy4->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy4->GetComponent<dae::EnemyComponent>()->SetKillPoints(250);
	goEnemy4->AddComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy4->GetComponent<dae::AIComponent>()->SetSpeed(50.f);
	goEnemy4->AddComponent<dae::TransformComponent>()->SetPosition(448.f, 416.f, 0.0f);

	goEnemy5->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy5->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy5->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer);
	if (m_pPlayer2) goEnemy4->GetComponent<dae::BoxTriggerComponent>()->AddOtherObject(m_pPlayer2);
	goEnemy5->GetComponent<dae::BoxTriggerComponent>()->DestroyOtherAfterOverLap(true);
	goEnemy5->GetComponent<dae::BoxTriggerComponent>()->DecMyHealthAfterOverlap(true);
	goEnemy5->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy5->GetComponent<dae::EnemyComponent>()->SetKillPoints(250);
	goEnemy5->AddComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy5->GetComponent<dae::AIComponent>()->SetSpeed(50.f);
	goEnemy5->AddComponent<dae::TransformComponent>()->SetPosition(192.f, 256.f, 0.0f);

	std::vector<std::shared_ptr<dae::GameObject>> goEnemies;
	goEnemies.emplace_back(goEnemy);
	goEnemies.emplace_back(goEnemy2);
	goEnemies.emplace_back(goEnemy3);
	goEnemies.emplace_back(goEnemy4);
	goEnemies.emplace_back(goEnemy5);

	m_pEnemiesLv3 = goEnemies;

	auto spawnBulletP1 = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());
	if (m_pPlayer2)
	{
		auto spawnBulletP2 = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer2.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());
		input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_RSHIFT, std::move(spawnBulletP2), 1);
	}
	auto spawnBulletGP = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBulletP1), 1);

	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::A, std::move(spawnBulletGP), 1);


	goEnemy->AddGameObject();
	goEnemy2->AddGameObject();
	goEnemy3->AddGameObject();
	goEnemy4->AddGameObject();
	goEnemy5->AddGameObject();

	goEnemy->Start();
	goEnemy2->Start();
	goEnemy3->Start();
	goEnemy4->Start();
	goEnemy5->Start();
}

int TronGameScene::GetLevel()
{
	return m_Level;
}