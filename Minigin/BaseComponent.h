#pragma once
namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Start() {};
		virtual void Update(float) {};
		virtual void Render() const {};
		virtual void ReceiveMessage(int) {};

		void SetGameObject(GameObject& gameObject);
		GameObject* GetGameObject() const;

	protected:
		GameObject* m_pGameObject{ nullptr };
	};
}


