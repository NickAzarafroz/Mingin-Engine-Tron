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

	class MoveTurretCommandP2 : public GameActorCommand
	{
	public:
		MoveTurretCommandP2(GameObject* actor, bool increase) : GameActorCommand(actor), m_Increase{ increase } {}
		virtual ~MoveTurretCommandP2() = default;

		MoveTurretCommandP2(const MoveTurretCommandP2& other) = delete;
		MoveTurretCommandP2(MoveTurretCommandP2&& other) = delete;
		MoveTurretCommandP2& operator=(const MoveTurretCommandP2& other) = delete;
		MoveTurretCommandP2& operator=(MoveTurretCommandP2&& other) = delete;

		void Execute() override;

	private:
		bool m_Increase{};

		static float m_Angle;
	};
}

