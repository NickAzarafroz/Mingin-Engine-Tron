#pragma once
#include <memory>
namespace dae
{
	class Scene;
	class MainMenuScene final
	{
	public:
		MainMenuScene(std::shared_ptr<Scene> pScene);
		~MainMenuScene() = default;

		MainMenuScene(const MainMenuScene& other) = delete;
		MainMenuScene(MainMenuScene&& other) = delete;
		MainMenuScene& operator=(const MainMenuScene& other) = delete;
		MainMenuScene& operator=(MainMenuScene&& other) = delete;

		void Load();

	private:
		std::shared_ptr<Scene> m_MainMenuScene;
	};
}

