#include "MoveCommand.h"
using namespace dae;

void MoveCommand::Execute()
{
	float x = GetGameActor()->GetWorldPosition().x;
	float y = GetGameActor()->GetWorldPosition().y;

	x += m_Speed * m_Dir.x * GetGameActor()->GetElapsedSec();
	y += m_Speed * m_Dir.y * GetGameActor()->GetElapsedSec();

	GetGameActor()->SetLocalPosition(glm::vec3(x, y, 0.0f));
}