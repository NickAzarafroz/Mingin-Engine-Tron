#pragma once
#include <memory>
namespace dae
{
	class Scene;
	class TronGameScene final
	{
	public:
		TronGameScene(std::shared_ptr<Scene> pScene);
		~TronGameScene() = default;

		TronGameScene(const TronGameScene& other) = delete;
		TronGameScene(TronGameScene&& other) = delete;
		TronGameScene& operator=(const TronGameScene& other) = delete;
		TronGameScene& operator=(TronGameScene&& other) = delete;

		void Load();

	private:
		std::shared_ptr<Scene> m_TronGameScene;
	};
}

