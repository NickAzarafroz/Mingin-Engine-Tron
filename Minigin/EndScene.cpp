#include "EndScene.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "PlayerComponent.h"
#include "GridComponent.h"
#include "TransformComponent.h"
using namespace dae;

EndScene::EndScene(std::shared_ptr<Scene> pScene) : m_EndScene{ pScene } {}

void EndScene::Load(int endscore)
{
	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);

	auto goScoreText = std::make_shared<dae::GameObject>(m_EndScene.get());
	auto goHighScoreText = std::make_shared<dae::GameObject>(m_EndScene.get());
	auto goScore1 = std::make_shared<dae::GameObject>(m_EndScene.get());
	auto goScore2 = std::make_shared<dae::GameObject>(m_EndScene.get());
	auto goScore3 = std::make_shared<dae::GameObject>(m_EndScene.get());
	auto goScore4 = std::make_shared<dae::GameObject>(m_EndScene.get());

	goScoreText->AddComponent<dae::TextComponent>()->SetText("YOUR SCORE: " + std::to_string(endscore));
	goScoreText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goScoreText->GetComponent<dae::TextComponent>()->SetFontColor(0, 0, 255);
	goScoreText->AddComponent<dae::TransformComponent>()->SetPosition(200.f, 30.f, 0.f);

	goHighScoreText->AddComponent<dae::TextComponent>()->SetText("HIGHSCORES:");
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goHighScoreText->GetComponent<dae::TextComponent>()->SetFontColor(255, 255, 0);
	goHighScoreText->AddComponent<dae::TransformComponent>()->SetPosition(180.f, 90.f, 0.f);

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

	goScore1->AddComponent<TextComponent>()->SetText(std::to_string(m_HighScores[0]));
	goScore1->GetComponent<TextComponent>()->SetFont(pTronFont);
	goScore1->GetComponent<TextComponent>()->SetFontColor(0, 255, 0);
	goScore1->AddComponent<TransformComponent>()->SetPosition(200.f, 150.f, 0.f);

	goScore2->AddComponent<TextComponent>()->SetText(std::to_string(m_HighScores[1]));
	goScore2->GetComponent<TextComponent>()->SetFont(pTronFont);
	goScore2->GetComponent<TextComponent>()->SetFontColor(0, 255, 0);
	goScore2->AddComponent<TransformComponent>()->SetPosition(200.f, 210.f, 0.f);

	goScore3->AddComponent<TextComponent>()->SetText(std::to_string(m_HighScores[2]));
	goScore3->GetComponent<TextComponent>()->SetFont(pTronFont);
	goScore3->GetComponent<TextComponent>()->SetFontColor(0, 255, 0);
	goScore3->AddComponent<TransformComponent>()->SetPosition(200.f, 270.f, 0.f);

	goScore4->AddComponent<TextComponent>()->SetText(std::to_string(m_HighScores[3]));
	goScore4->GetComponent<TextComponent>()->SetFont(pTronFont);
	goScore4->GetComponent<TextComponent>()->SetFontColor(0, 255, 0);
	goScore4->AddComponent<TransformComponent>()->SetPosition(200.f, 320.f, 0.f);

	goScoreText->AddGameObject();
	goHighScoreText->AddGameObject();
	goScore1->AddGameObject();
	goScore2->AddGameObject();
	goScore3->AddGameObject();
	goScore4->AddGameObject();

	m_EndScene->Start();
}

void EndScene::Load()
{
	auto pTronFont = dae::ResourceManager::GetInstance().LoadFont("Tr2n.ttf", 30);

	auto goWinnerText = std::make_shared<dae::GameObject>(m_EndScene.get());

	goWinnerText->AddComponent<dae::TextComponent>()->SetText("WINNER IS: ");
	goWinnerText->GetComponent<dae::TextComponent>()->SetFont(pTronFont);
	goWinnerText->GetComponent<dae::TextComponent>()->SetFontColor(0, 0, 255);
	goWinnerText->AddComponent<dae::TransformComponent>()->SetPosition(150.f, 30.f, 0.f);

	for (const auto& object : SceneManager::GetInstance().GetScene(1).GetAllObjects())
	{
		if (object->GetComponent<PlayerComponent>())
		{
			object->SetScene(m_EndScene.get());
			object->AddGameObject();
		}

		if(object->GetComponent<GridComponent>())
		{
			object->SetScene(m_EndScene.get());
			object->AddGameObject();
		}
	}

	goWinnerText->AddGameObject();

	m_EndScene->Start();
}
