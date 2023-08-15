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
#include "GoToNextSceneCommand.h"
#include "ValidCellComponent.h"
#include "AliveComponent.h"
#include "Scene.h"
using namespace dae;

TronGameScene::TronGameScene(std::shared_ptr<Scene> pScene) : m_TronGameScene{ pScene }
{
	
}

void TronGameScene::Load()
{
	auto& input = dae::InputManager::GetInstance();

	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);
	auto pFontFpsText = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);

	//auto goLogo = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHighScoreText = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHighScoreValue = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer1Text = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goFPS = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayer = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goGrid = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goHealth = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goPlayerTurret = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	//Logo Texture
	//-----------------------------------------------------------------------
	//goLogo->AddComponent<dae::TextureComponent>()->SetTexture("logo.tga");
	//goLogo->SetLocalPosition(glm::vec3(216.f, 180.f, 0.f));
	//--------------------------------------------------------------------------

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
	goPlayer->AddComponent<dae::PlayerComponent>();
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
	goEnemy->AddComponent<dae::AIComponent>()->SetObjectToShoot(goPlayer);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(288.f, 320.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->SetObjectToShoot(goPlayer);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(goGrid->GetComponent<dae::GridComponent>());
	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(384.f, 352.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(goPlayer.get());
	goEnemy3->AddComponent<dae::AIComponent>()->SetObjectToShoot(goPlayer);
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
	goHealth->AddComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHealth->GetComponent<dae::TextComponent>()->SetFontColor(255, 0, 255);

	goHealth->AddComponent<dae::LiveDisplayComponent>()->SetObjectToDisplayLives(goPlayer.get());
	goHealth->AddComponent<dae::TransformComponent>()->SetPosition(0.f, 50.f, 0.f);

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

	auto spawnBullet = std::make_unique<dae::SpawnBulletCommand>(goPlayer.get(), goEnemies, goGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_D, std::move(gridRight), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_A, std::move(gridLeft), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_S, std::move(gridDown), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_W, std::move(gridUp), 0);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBullet), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_UP, std::move(incTurret), 1);
	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_DOWN, std::move(decTurret), 1);

	auto p0 = std::make_unique<dae::XBox360Controller>(0);

	auto moveRightCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveLeftCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ -1.f, 0.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveUpCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, -1.f }, goGrid->GetComponent<dae::GridComponent>());
	auto moveDownCommand = std::make_unique<dae::MoveGridCommand>(goPlayer.get(), glm::vec2{ 0.f, 1.f }, goGrid->GetComponent<dae::GridComponent>());

	input.AddController(std::move(p0));

	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadRight, std::move(moveRightCommand));
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadLeft, std::move(moveLeftCommand));
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadUp, std::move(moveUpCommand));
	input.BindCommandController(0, dae::XBox360Controller::ControllerButton::DPadDown, std::move(moveDownCommand));

	goPlayer->SendMessageID(0);

	goPlayerTurret->SetParent(goPlayer.get(), true);

	m_pPlayer = goPlayer;
	m_pGrid = goGrid;

	goGrid->AddGameObject();
	goHighScoreText->AddGameObject();
	goHighScoreValue->AddGameObject();
	goPlayer1Text->AddGameObject();
	goFPS->AddGameObject();
	goPlayer->AddGameObject();
	goHealth->AddGameObject();
	goEnemy->AddGameObject();
	goEnemy2->AddGameObject();
	goEnemy3->AddGameObject();

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

	m_pGrid->GetComponent<GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron.json");

	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(288.f, 320.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(384.f, 352.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy3->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy3->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(192.f, 192.f, 0.0f);

	std::vector<std::shared_ptr<dae::GameObject>> goEnemies;
	goEnemies.emplace_back(goEnemy);
	goEnemies.emplace_back(goEnemy2);
	goEnemies.emplace_back(goEnemy3);

	m_pEnemiesLv1 = goEnemies;

	auto spawnBullet = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBullet), 1);

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

	m_pGrid->GetComponent<GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron2.json");

	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy4 = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(384.f, 128.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(128.f, 384.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	//goEnemy3->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy3->AddComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy3->GetComponent<dae::AIComponent>()->SetSpeed(50.f);

	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(544.f, 192.f, 0.0f);

	goEnemy4->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy4->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy4->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	//goEnemy4->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy4->AddComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy4->GetComponent<dae::AIComponent>()->SetSpeed(50.f);

	goEnemy4->AddComponent<dae::TransformComponent>()->SetPosition(544.f, 448.f, 0.0f);

	std::vector<std::shared_ptr<dae::GameObject>> goEnemies;
	goEnemies.emplace_back(goEnemy);
	goEnemies.emplace_back(goEnemy2);
	goEnemies.emplace_back(goEnemy3);
	goEnemies.emplace_back(goEnemy4);

	m_pEnemiesLv2 = goEnemies;

	auto spawnBullet = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBullet), 1);

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

	m_pGrid->GetComponent<GridComponent>()->Initialize(32.f, 32.f, "../Data/LevelTron3.json");

	auto goEnemy = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy2 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy3 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy4 = std::make_shared<dae::GameObject>(m_TronGameScene.get());
	auto goEnemy5 = std::make_shared<dae::GameObject>(m_TronGameScene.get());

	goEnemy->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy->AddComponent<dae::TransformComponent>()->SetPosition(224.f, 256.f, 0.0f);

	goEnemy2->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy2->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy2->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy2->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy2->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy2->AddComponent<dae::TransformComponent>()->SetPosition(192.f, 416.f, 0.0f);

	goEnemy3->AddComponent<dae::TextureComponent>()->SetTexture("BlueTank.png");
	goEnemy3->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy3->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	goEnemy3->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy3->GetComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());

	goEnemy3->AddComponent<dae::TransformComponent>()->SetPosition(416.f, 224.f, 0.0f);

	goEnemy4->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy4->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy4->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	//goEnemy4->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
	goEnemy4->AddComponent<dae::AIComponent>()->SetGrid(m_pGrid->GetComponent<dae::GridComponent>());
	goEnemy4->GetComponent<dae::AIComponent>()->SetSpeed(50.f);

	goEnemy4->AddComponent<dae::TransformComponent>()->SetPosition(448.f, 416.f, 0.0f);

	goEnemy5->AddComponent<dae::TextureComponent>()->SetTexture("Recognizer.png");
	goEnemy5->AddComponent<dae::BoxTriggerComponent>()->SetSize(32.f, 32.f);
	goEnemy5->AddComponent<dae::EnemyComponent>()->SetPlayer(m_pPlayer.get());
	//goEnemy4->AddComponent<dae::AIComponent>()->SetObjectToShoot(m_pPlayer);
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

	auto spawnBullet = std::make_unique<dae::SpawnBulletCommand>(m_pPlayer.get(), goEnemies, m_pGrid->GetComponent<dae::GridComponent>());

	input.BindCommandKeyBoard(SDL_Scancode::SDL_SCANCODE_SPACE, std::move(spawnBullet), 1);

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