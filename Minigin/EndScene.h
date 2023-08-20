#pragma once
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
namespace dae
{
	class Scene;
	class EndScene final
	{
	public:
		EndScene(std::shared_ptr<Scene> pScene);
		~EndScene() = default;

		EndScene(const EndScene& other) = delete;
		EndScene(EndScene&& other) = delete;
		EndScene& operator=(const EndScene& other) = delete;
		EndScene& operator=(EndScene&& other) = delete;

		void Load(int endscore);
		void Load();

	private:
		std::shared_ptr<Scene> m_EndScene;
		std::vector<int> m_HighScores;
	};
}

