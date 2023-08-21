#include "EndScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "ServiceLocator.h"
using namespace dae;

EndScene::EndScene(std::shared_ptr<Scene> pScene) : m_EndScene{ pScene } {}

void EndScene::Load(int endscore)
{
	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);
	auto& soundsystem = dae::ServiceLocator::GetSoundSystem();

	soundsystem.Stop();
	soundsystem.Play("../Data/FailMusic.mp3", 20.f, 0);

	auto goScoreText = std::make_shared<GameObject>(m_EndScene.get());
	auto goHighScoreText = std::make_shared<GameObject>(m_EndScene.get());

	std::vector<std::shared_ptr<GameObject>> goScores{};

	for(int i{}; i < 10; ++i)
	{
		goScores.emplace_back(std::make_shared<GameObject>(m_EndScene.get()));
	}

	goScoreText->AddComponent<TextComponent>()->SetText("YOUR SCORE: " + std::to_string(endscore));
	goScoreText->GetComponent<TextComponent>()->SetFont(pTronFont);
	goScoreText->GetComponent<TextComponent>()->SetFontColor(0, 0, 255);
	goScoreText->AddComponent<TransformComponent>()->SetPosition(200.f, 30.f, 0.f);

	goHighScoreText->AddComponent<TextComponent>()->SetText("HIGHSCORES:");
	goHighScoreText->GetComponent<TextComponent>()->SetFont(pTronFont);
	goHighScoreText->GetComponent<TextComponent>()->SetFontColor(255, 255, 0);
	goHighScoreText->AddComponent<TransformComponent>()->SetPosition(180.f, 90.f, 0.f);

	auto inputFile = ResourceManager::GetInstance().ReadFile("HighScore.txt");

	if (inputFile.is_open())
	{
		int score{};

		while (inputFile >> score)
		{
			m_HighScores.emplace_back(score);
		}

		inputFile.close();


		auto minScoreIt = std::min_element(m_HighScores.begin(), m_HighScores.end());
		if (endscore > *minScoreIt) 
		{
			*minScoreIt = endscore; 
		}

		std::sort(m_HighScores.begin(), m_HighScores.end(), std::greater<int>());

		auto outputFile = ResourceManager::GetInstance().WriteToFile("HighScore.txt");

		if (outputFile.is_open())
		{
			for (int i{}; i < m_HighScores.size(); ++i)
			{
				outputFile << m_HighScores[i] << "\n";
			}

			outputFile.close();
		}
	}

	float inc{ 30.f };

	for (int i{}; i < goScores.size(); ++i)
	{
		goScores[i]->AddComponent<TextComponent>()->SetText(std::to_string(m_HighScores[i]));
		goScores[i]->GetComponent<TextComponent>()->SetFont(pTronFont);
		goScores[i]->GetComponent<TextComponent>()->SetFontColor(0, 255, 0);
		goScores[i]->AddComponent<TransformComponent>()->SetPosition(200.f, 120.f + inc, 0.f);

		goScores[i]->AddGameObject();
		inc += 30.f;
	}

	goScoreText->AddGameObject();
	goHighScoreText->AddGameObject();

	m_EndScene->Start();
}

void EndScene::Load()
{
	auto pTronFont = ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 60);
	auto& soundsystem = ServiceLocator::GetSoundSystem();

	soundsystem.Stop();
	soundsystem.Play("../Data/FailMusic.mp3", 20.f, 0);

	auto goWinnerText = std::make_shared<dae::GameObject>(m_EndScene.get());
	auto goWinner = std::make_shared<dae::GameObject>(m_EndScene.get());

	for (const auto& object : SceneManager::GetInstance().GetScene(1).GetAllObjects())
	{
		if (object->GetComponent<PlayerComponent>())
		{
			auto winnerName = object->GetComponent<PlayerComponent>()->GetName();

			goWinnerText->AddComponent<TextComponent>()->SetText("WINNER IS: ");
			goWinnerText->GetComponent<TextComponent>()->SetFont(pTronFont);
			goWinnerText->GetComponent<TextComponent>()->SetFontColor(0, 0, 255);
			goWinnerText->AddComponent<TransformComponent>()->SetPosition(150.f, 60.f, 0.f);

			goWinner->AddComponent<TextComponent>()->SetText(winnerName);
			goWinner->GetComponent<TextComponent>()->SetFont(pTronFont);

			if (winnerName == "Player1") 
			{
				goWinner->GetComponent<TextComponent>()->SetFontColor(255, 0, 0);
			} 
			else 
			{
				goWinner->GetComponent<TextComponent>()->SetFontColor(255, 0, 255);
			}

			goWinner->AddComponent<TransformComponent>()->SetPosition(200.f, 200.f, 0.f);
		}
	}

	goWinnerText->AddGameObject();
	goWinner->AddGameObject();

	m_EndScene->Start();
}
