#include "ChangeModeCommand.h"
#include "TextComponent.h"
using namespace dae;

int ChangeModeCommand::m_ModeIndex{};

void ChangeModeCommand::Execute()
{
	switch (m_ModeIndex)
	{
	case -1:
		++m_ModeIndex;
		GetGameActor()->GetComponent<TextComponent>()->SetText(m_Modes[m_ModeIndex]);
		break;
	case 0: 
		++m_ModeIndex;
		GetGameActor()->GetComponent<TextComponent>()->SetText(m_Modes[m_ModeIndex]);
		break;
	case 1: 
		++m_ModeIndex;
		GetGameActor()->GetComponent<TextComponent>()->SetText(m_Modes[m_ModeIndex]);
		m_ModeIndex = -1;
		break;
	default:
		break;
	}
}
