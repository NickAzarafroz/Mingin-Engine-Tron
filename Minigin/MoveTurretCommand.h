#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class MoveTurretCommand : public GameActorCommand 
	{
	public:
		MoveTurretCommand(GameObject* actor, bool increase) : GameActorCommand(actor), m_Increase{ increase } {}
		virtual ~MoveTurretCommand() = default;

		MoveTurretCommand(const MoveTurretCommand& other) = delete;
		MoveTurretCommand(MoveTurretCommand&& other) = delete;
		MoveTurretCommand& operator=(const MoveTurretCommand& other) = delete;
		MoveTurretCommand& operator=(MoveTurretCommand&& other) = delete;

		void Execute() override;

	private:
		bool m_Increase{};

		static float m_Angle;
	};
}

