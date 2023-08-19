#pragma once
#include <memory>
#include <map>
#include <vector>
#include <Windows.h>
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include "XBox360Controller.h"
#include <SDL.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		void AddController(std::unique_ptr<XBox360Controller> controller);
		void BindCommandController(unsigned controllerIndex, XBox360Controller::ControllerButton button, std::unique_ptr<Command> command, int state);
		void BindCommandKeyBoard(SDL_Scancode keyBoardkey, std::unique_ptr<Command> command, int state);
		void UnbindCommandController(unsigned controllerIndex, XBox360Controller::ControllerButton button);
		void UnbindCommandKeyBoard(SDL_Scancode keyBoardkey);

	private:
		//XINPUT_STATE m_CurrentState;
		using ControllerKey = std::pair<unsigned, XBox360Controller::ControllerButton>;
		using ControllerCommandsMap = std::map<ControllerKey, std::pair<int, std::unique_ptr<Command>>>;
		ControllerCommandsMap m_ConsoleCommands{};
		std::vector<std::unique_ptr<XBox360Controller>> m_Controllers{};

		SDL_Scancode m_KeyboardKey;
		using KeyBoardCommandsMap = std::map<SDL_Scancode, std::pair<int, std::unique_ptr<Command>>>;
		KeyBoardCommandsMap m_KeyBoardCommands{};
	};

}
