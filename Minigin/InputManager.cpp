#include <SDL.h>
#include "InputManager.h"
#include "../3rdParty/imgui-1.89.4/backends/imgui_impl_sdl.h"
#include <iostream>

bool dae::InputManager::ProcessInput()
{
	/*ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);*/

	for(auto& controller : m_Controllers)
	{
		controller->Update();
		unsigned controllerIndex = controller->GetControllerIndex();

		for(const auto& [controllerKey, command] : m_ConsoleCommands)
		{
			if(controllerKey.first == controllerIndex && controller->IsPressed(controllerKey.second))
			{
				command->Execute();
			}
		}
	}

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	for(const auto& [keyBoardKey, command] : m_KeyBoardCommands)
	{
		if(pStates[keyBoardKey])
		{
			command->Execute();
		}
	}

	SDL_Event e;
	while (SDL_PollEvent(&e)) 
	{
		if (e.type == SDL_QUIT) 
		{
			return false;
		}
		if (e.type == SDL_KEYUP) 
		{
			if (e.key.keysym.sym == SDLK_a) 
			{
				//std::cout << "A pressed";
			}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) 
		{
			
		}
		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}
	return true;
}

void dae::InputManager::AddController(std::unique_ptr<XBox360Controller> controller)
{
	m_Controllers.push_back(std::move(controller));
}

void dae::InputManager::BindCommandController(unsigned controllerIndex, XBox360Controller::ControllerButton button, std::unique_ptr<Command> command)
{
	m_ConsoleCommands[ControllerKey(controllerIndex, button)] = std::move(command);
}

void dae::InputManager::BindCommandKeyBoard(SDL_Scancode keyBoardkey, std::unique_ptr<Command> command)
{
	m_KeyBoardCommands[keyBoardkey] = std::move(command);
}
