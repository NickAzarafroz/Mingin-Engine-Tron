#pragma once
#include <memory>
#include <string>
#include <array>
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
		std::array<std::string, 3> m_Gamemodes{};
	};
}

