#pragma once
#include "GameActorCommand.h"
namespace dae
{
	class SkipLevelCommand : public GameActorCommand
	{
	public:
		SkipLevelCommand(GameObject* actor) : GameActorCommand(actor) {}
		virtual ~SkipLevelCommand() = default;

		SkipLevelCommand(const SkipLevelCommand& other) = delete;
		SkipLevelCommand(SkipLevelCommand&& other) = delete;
		SkipLevelCommand& operator=(const SkipLevelCommand& other) = delete;
		SkipLevelCommand& operator=(SkipLevelCommand&& other) = delete;

		void Execute() override;
	};
}
