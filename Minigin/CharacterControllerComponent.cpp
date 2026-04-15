#include "CharacterControllerComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Components/BoxColliderComponent.h"

dae::CharacterControllerComponent::CharacterControllerComponent(GameObject* pOwner, float speed)
	: Component{ pOwner }
    , m_speed{ speed }
{
    m_pSubject = std::make_unique<Subject>();
}

dae::CharacterControllerComponent::~CharacterControllerComponent()
{
    m_pSubject->NotifyObservers(Event(make_sdbm_hash("OnSubjectDestroyed")), GetOwner());
}

void dae::CharacterControllerComponent::Update(float deltaTime)
{
    if (!m_checkedForCollider)
    {
        m_pCollider = GetOwner()->GetComponent<BoxColliderComponent>();
        m_checkedForCollider = true;
    }

    bool isMoving{ IsMoving() };

    SendEvents(isMoving);

    m_wasMovingLastFrame = isMoving;

    if (isMoving)
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

bool dae::CharacterControllerComponent::IsMoving() const
{
    return (m_moveDirection.x * m_moveDirection.x + m_moveDirection.y * m_moveDirection.y > FLT_EPSILON);
}

void dae::CharacterControllerComponent::SendEvents(bool isMoving)
{
    if (!m_wasMovingLastFrame && isMoving)
    {
        m_pSubject->NotifyObservers(Event(make_sdbm_hash("OnStartedMoving")), GetOwner());
    }
    else if (m_wasMovingLastFrame && !isMoving)
    {
        m_pSubject->NotifyObservers(Event(make_sdbm_hash("OnStoppedMoving")), GetOwner());
    }
}
