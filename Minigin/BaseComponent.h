#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual void Start() = 0;
		virtual void Update(float elapsedSec) = 0;
		virtual void Render() const = 0;

		void SetGameObject(GameObject& gameObject) { m_pGameObject = &gameObject; };
		virtual ~BaseComponent();

	protected:
		GameObject* m_pGameObject{ nullptr };
	};
}


