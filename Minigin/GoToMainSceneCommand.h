#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class GoToMainSceneCommand : public GameActorCommand
	{
	public:
		GoToMainSceneCommand(GameObject* actor) : GameActorCommand(actor) {}
		virtual ~GoToMainSceneCommand() = default;

		GoToMainSceneCommand(const GoToMainSceneCommand& other) = delete;
		GoToMainSceneCommand(GoToMainSceneCommand&& other) = delete;
		GoToMainSceneCommand& operator=(const GoToMainSceneCommand& other) = delete;
		GoToMainSceneCommand& operator=(GoToMainSceneCommand&& other) = delete;

		void Execute() override;
	};
}

