#include "TransformComponent.h"
using namespace dae;

void TransformComponent::Start() {};

void TransformComponent::Update(float) {};

void TransformComponent::Render() const {};

void TransformComponent::SetPosition(float x, float y)
{
	m_transform.x = x;
	m_transform.y = y;
}

const glm::vec3& TransformComponent::GetPosition() const
{
	return m_transform;
}

TransformComponent::~TransformComponent()
{

}