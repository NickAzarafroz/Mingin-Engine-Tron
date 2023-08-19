#include "MoveTurretCommand.h"
#include "TextureComponent.h"
using namespace dae;

float MoveTurretCommand::m_Angle{};
float MoveTurretCommandP2::m_Angle{};

void MoveTurretCommand::Execute()
{
	if (m_Angle == 360.f || m_Angle == -360.f)
	{
		m_Angle = 0.f;
	}

	if (m_Increase)
	{
		m_Angle -= 45.f;
	}
	else
	{
		m_Angle += 45.f;
	}

	GetGameActor()->GetComponent<TextureComponent>()->SetAngle(m_Angle);
}

void MoveTurretCommandP2::Execute()
{
	if (m_Angle == 360.f || m_Angle == -360.f)
	{
		m_Angle = 0.f;
	}

	if (m_Increase)
	{
		m_Angle -= 45.f;
	}
	else
	{
		m_Angle += 45.f;
	}

	GetGameActor()->GetComponent<TextureComponent>()->SetAngle(m_Angle);
}

