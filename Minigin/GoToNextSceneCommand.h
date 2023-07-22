#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class GoToNextSceneCommand : public GameActorCommand
	{
	public:
		GoToNextSceneCommand(GameObject* actor) : GameActorCommand(actor) {}
		virtual ~GoToNextSceneCommand() = default;

		GoToNextSceneCommand(const GoToNextSceneCommand& other) = delete;
		GoToNextSceneCommand(GoToNextSceneCommand&& other) = delete;
		GoToNextSceneCommand& operator=(const GoToNextSceneCommand& other) = delete;
		GoToNextSceneCommand& operator=(GoToNextSceneCommand&& other) = delete;

		void Execute() override;
	};
}

