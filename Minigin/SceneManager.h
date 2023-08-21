#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Scene;
	class MainMenuScene;
	class TronGameScene;
	class EndScene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetScene(int index);

		void Initialize();
		void ResetEnemies();
		void LoadLevel1();
		void LoadLevel2();
		void LoadLevel3();

		void GoNextScene();
		int GetCurrentSceneIndex();
		void SetCurrentSceneIndex(int index);

		int GetLevel();

		void LoadMainGame(int mode);
		void LoadEndScene(int endscore);
		void LoadEndScene();

		void Start();
		void Update(float elapsedSec);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_pScenes;
		std::shared_ptr<MainMenuScene> m_MainMenuScene;
		std::shared_ptr<TronGameScene> m_TronGameScene;
		std::shared_ptr<EndScene> m_EndScene;
		int m_ActiveSceneIndex{ 0 };
		int m_Level{};
	};
}
