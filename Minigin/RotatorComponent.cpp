#include "RotatorComponent.h"
#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float radius, float angularVelocity)
	: Component(pOwner)
	, m_radius{ radius }, m_angularVelocity{ angularVelocity }
{
}

void dae::RotatorComponent::Update(float deltaTime)
{
	float deltaAngle = m_angularVelocity * deltaTime;

	if (fabsf(deltaAngle) < FLT_EPSILON) return;

	m_angle += deltaAngle;

	GetOwner()->SetLocalPosition(
		{
			m_radius * cosf(m_angle),
			m_radius * sinf(m_angle),
			0.0f
		}
	);
}
