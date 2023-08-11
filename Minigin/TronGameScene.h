#pragma once
#include <memory>
#include <vector>
namespace dae
{
	class Scene;
	class GameObject;
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
		void ResetEnemies();
		void LoadLevel2();

	private:
		std::shared_ptr<Scene> m_TronGameScene;
		std::vector<std::shared_ptr<GameObject>> m_pEnemiesLv1;
		std::shared_ptr<GameObject> m_pPlayer;
		std::shared_ptr<GameObject> m_pGrid;
	};
}

