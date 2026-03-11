#include "CharacterControllerComponent.h"
#include "GameObject.h"

dae::CharacterControllerComponent::CharacterControllerComponent(GameObject* pOwner, float speed)
	: Component{ pOwner }
    , m_speed{ speed }
{
}

void dae::CharacterControllerComponent::Update(float deltaTime)
{
    float sqrLength = m_moveDirection.x * m_moveDirection.x + m_moveDirection.y * m_moveDirection.y;
    
    if (sqrLength > FLT_EPSILON)
    {
        auto direction = glm::normalize(m_moveDirection);

        auto position = GetOwner()->GetTransform()->GetLocalPosition();

        position.x += direction.x * m_speed * deltaTime;
        position.y += direction.y * m_speed * deltaTime;

        GetOwner()->SetLocalPosition(position);

        m_moveDirection = { 0, 0 };
    }
}

void dae::CharacterControllerComponent::SetSpeed(float speed)
{
    m_speed = speed;
}

void dae::CharacterControllerComponent::SetMoveDirection(const glm::vec2& direction)
{
    m_moveDirection += direction;
}
