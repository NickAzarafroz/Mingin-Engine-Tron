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
	//TODO: NEEDS TO BE CHANGED SO THE USER CAN DECIDE IF HE WANTS TO HAVE THAT
	bool commandExecuted = false;
	
	for(const auto& [keyBoardKey, command] : m_KeyBoardCommands)
	{
		if(pStates[keyBoardKey] && command.first == 0)
		{
			if (!commandExecuted)
			{
				command.second->Execute();
				commandExecuted = true;
			}
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
			for (const auto& [keyBoardKey, command] : m_KeyBoardCommands)
			{
				if (keyBoardKey == e.key.keysym.scancode && command.first == 1)
				{
					command.second->Execute();
					break;
				}
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
	m_Controllers.emplace_back(std::move(controller));
}

void dae::InputManager::BindCommandController(unsigned controllerIndex, XBox360Controller::ControllerButton button, std::unique_ptr<Command> command)
{
	m_ConsoleCommands[ControllerKey(controllerIndex, button)] = std::move(command);
}

void dae::InputManager::BindCommandKeyBoard(SDL_Scancode keyBoardkey, std::unique_ptr<Command> command, int state)
{
	m_KeyBoardCommands[keyBoardkey].first = state;
	m_KeyBoardCommands[keyBoardkey].second = std::move(command);
}

void dae::InputManager::UnbindCommandController(unsigned controllerIndex, XBox360Controller::ControllerButton button)
{
	for (auto it = m_ConsoleCommands.begin(); it != m_ConsoleCommands.end(); ++it)
	{
		if (it->first.first == controllerIndex && it->first.second == button)
		{
			m_ConsoleCommands.erase(it);
			break;
		}
	}
}

void dae::InputManager::UnbindCommandKeyBoard(SDL_Scancode keyBoardkey)
{
	for(auto it = m_KeyBoardCommands.begin(); it != m_KeyBoardCommands.end(); ++it)
	{
		if(it->first == keyBoardkey)
		{
			m_KeyBoardCommands.erase(it);
			break;
		}
	}
}
