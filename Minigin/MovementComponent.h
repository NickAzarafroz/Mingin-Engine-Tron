#include "BaseComponent.h"

namespace dae
{
	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent() = default;
		~MovementComponent() = default;

		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;

		virtual void Start();
		virtual void Update(float elapsedSec) override;

		void SetSpeed(float speed, float x, float y);

	private:
		float m_PosX;
		float m_PosY;

		float m_Speed;

		float m_DirX;
		float m_DirY;
	};
}
