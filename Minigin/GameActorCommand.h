#pragma once
#include "Command.h"
#include "GameObject.h"
namespace dae
{
	class GameActorCommand : public Command
	{
	public:
		GameActorCommand(GameObject* pActor) : m_pActor{ pActor } {};
		virtual ~GameActorCommand() = default;

		GameActorCommand(const GameActorCommand& other) = delete;
		GameActorCommand(GameActorCommand&& other) = delete;
		GameActorCommand& operator=(const GameActorCommand& other) = delete;
		GameActorCommand& operator=(GameActorCommand&& other) = delete;

	protected:
		GameObject* GetGameActor() const { return m_pActor; }

	private:
		GameObject* m_pActor;
	};
}