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
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		Scene& GetScene(int index);

		void Initialize();

		void GoNextScene();

		int GetCurrentSceneIndex();

		void Start();
		void Update(float elapsedSec);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::shared_ptr<MainMenuScene> m_MainMenuScene;
		std::shared_ptr<TronGameScene> m_TronGameScene;
		int m_ActiveSceneIndex{ 0 };
	};
}
