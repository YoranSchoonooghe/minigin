#include "CharacterControllerComponent.h"
#include "CharacterControllerComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Components/BoxColliderComponent.h"

dae::CharacterControllerComponent::CharacterControllerComponent(GameObject* pOwner, float speed)
	: Component{ pOwner }
    , m_speed{ speed }
{
}

void dae::CharacterControllerComponent::Update(float deltaTime)
{
    if (!m_checkedForCollider)
    {
        m_pCollider = GetOwner()->GetComponent<BoxColliderComponent>();
        m_checkedForCollider = true;
    }

    float sqrLength = m_moveDirection.x * m_moveDirection.x + m_moveDirection.y * m_moveDirection.y;
    
    if (sqrLength > FLT_EPSILON)
    {
        auto direction = glm::normalize(m_moveDirection);

        auto position = GetOwner()->GetLocalPosition();

        glm::vec2 displacement{};
        displacement.x = direction.x * m_speed * deltaTime;
        displacement.y = direction.y * m_speed * deltaTime;

        if (m_pCollider)
        {
            MoveAndSlide({ displacement.x, displacement.y });
        }
        else
        {
            position.x += displacement.x;
            position.y += displacement.y;

            GetOwner()->SetLocalPosition(position);
        }

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

void dae::CharacterControllerComponent::MoveAndSlide(const glm::vec2& displacement)
{
    SceneManager::GetInstance().GetActiveScene()->GetCollisionSystem()->MoveAndSlide(m_pCollider, displacement);
}
