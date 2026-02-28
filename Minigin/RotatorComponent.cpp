#include "RotatorComponent.h"
#include "GameObject.h"
#include <glm/gtc/constants.hpp>

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float radius, float angularVelocity)
	: Component(pOwner)
	, m_radius{ radius }, m_angularVelocity{ angularVelocity }
{
}

void dae::RotatorComponent::Update(float deltaTime)
{
	if (fabsf(m_angularVelocity) < FLT_EPSILON) return;

	m_angle += m_angularVelocity * deltaTime;

	WrapAngle(m_angle);

	GetOwner()->SetLocalPosition(
		{
			m_radius * cosf(m_angle),
			m_radius * sinf(m_angle),
			0.0f
		}
	);
}

float dae::RotatorComponent::WrapAngle(float angle) const
{
	constexpr float pi = glm::pi<float>();
	constexpr float twoPi = glm::two_pi<float>();

	angle = fmodf(angle + pi, twoPi);
	if (angle < 0) angle += twoPi;
	angle -= pi;

	return angle;
}
