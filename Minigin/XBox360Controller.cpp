#include "XBox360Controller.h"
#include <Xinput.h>
using namespace dae;

class XBox360Controller::XBox360ControllerImpl
{
private:
	XINPUT_STATE m_PreviousState{};
	XINPUT_STATE m_CurrentState{};
	unsigned int m_ControllerIndex{};
	int m_ButtonsPressedThisFrame{};
	int m_ButtonsReleasedThisFrame{};

public:
	XBox360ControllerImpl(int controllerIndex)
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

		m_ControllerIndex = controllerIndex;
	}

	void Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
	}

	bool IsDownThisFrame(unsigned int button) const
	{
		return m_ButtonsPressedThisFrame & button;
	}

	bool IsUpThisFrame(unsigned int button) const
	{
		return m_ButtonsReleasedThisFrame & button;
	}

	bool IsPressed(unsigned int button) const
	{
		return m_CurrentState.Gamepad.wButtons & button;
	}

	int GetControllerIndex()
	{
		return m_ControllerIndex;
	}
};

XBox360Controller::XBox360Controller(unsigned int controllerIndex)
{
	pImpl = new XBox360ControllerImpl(controllerIndex);
}

XBox360Controller::~XBox360Controller()
{
	delete pImpl;
}

void XBox360Controller::Update()
{
	pImpl->Update();
}

bool XBox360Controller::IsDownThisFrame(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool XBox360Controller::IsUpThisFrame(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool XBox360Controller::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<unsigned int>(button));
}

unsigned int XBox360Controller::GetControllerIndex()
{
	return pImpl->GetControllerIndex();
}
