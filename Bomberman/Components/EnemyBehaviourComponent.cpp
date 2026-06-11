#include "EnemyBehaviourComponent.h"
#include "GameObject.h"
#include "Components/CharacterControllerComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/AnimationControllerComponent.h"
#include "Components/HealthComponent.h"
#include "Events/EventManager.h"
#include <cassert>
#include <cstdlib>

dae::EnemyBehaviourComponent::EnemyBehaviourComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	m_pCharacterController = GetOwner()->GetComponent<CharacterControllerComponent>();
	assert(m_pCharacterController != nullptr && "EnemyBehaviourComponent: GameObject is missing a CharacterControllerComponent!");

	auto pBoxCollider = GetOwner()->GetComponent<BoxColliderComponent>();
	assert(pBoxCollider != nullptr && "BombermanComponent: GameObject is missing a BoxColliderComponent!");

	m_pBoxColliderComponentSubject = pBoxCollider->GetSubject();
	m_pBoxColliderComponentSubject->AddObserver(this);

	m_pAnimationController = GetOwner()->GetComponent<AnimationControllerComponent>();
	assert(m_pCharacterController != nullptr && "EnemyBehaviourComponent: GameObject is missing an AnimationControllerComponent!");

	auto* pHealthComponent = GetOwner()->GetComponent<HealthComponent>();
	assert(pHealthComponent != nullptr && "EnemyBehaviourComponent: GameObject is missing a HealthComponent!");

	m_pHealthComponentSubject = pHealthComponent->GetSubject();
	m_pHealthComponentSubject->AddObserver(this);
}

dae::EnemyBehaviourComponent::~EnemyBehaviourComponent()
{
	if (m_pBoxColliderComponentSubject)
	{
		m_pBoxColliderComponentSubject->RemoveObserver(this);
	}

	if (m_pHealthComponentSubject)
	{
		m_pHealthComponentSubject->RemoveObserver(this);
	}
}

void dae::EnemyBehaviourComponent::Update(float)
{
	//auto const worldPosition = GetOwner()->GetWorldPosition();

	//bool xIsEven{ false };
	//if ((std::fmodf(worldPosition.x - 64.0f, 128.0f)) < 2.0f)
	//{
	//	xIsEven = true;
	//}

	//bool yIsEven{ false };
	//if ((std::fmodf(worldPosition.y - 224.0f - 64.0f, 128.0f)) < 2.0f)
	//{
	//	yIsEven = true;
	//}

	//if (xIsEven && yIsEven)
	//{
	//	if (m_moveDirection.x == 0)
	//	{

	//	}
	//	else if (m_moveDirection.y == 0)
	//	m_moveDirection *= -1;
	//}

	m_pCharacterController->SetMoveDirection(m_moveDirection);
	m_pAnimationController->UpdateDirection(m_moveDirection);
}

void dae::EnemyBehaviourComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnColliderHit"):
		RandomizeMoveDirection();
		break;
	case make_sdbm_hash("OnDied"):
		EventManager::GetInstance().SendEvent(Event(make_sdbm_hash("OnEnemyDied")), GetOwner());
		GetOwner()->Destroy();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pBoxColliderComponentSubject = nullptr;
		m_pHealthComponentSubject = nullptr;
		break;
	}
}

void dae::EnemyBehaviourComponent::RandomizeMoveDirection()
{
	auto randomNumber{ rand() % 2 };

	if (randomNumber == 1)
	{
		m_moveDirection *= -1;
		return;
	}

	if (m_moveDirection == glm::vec2(1, 0) || m_moveDirection == glm::vec2(-1, 0))
	{
		m_moveDirection = glm::vec2(0, 1);
	}
	else
	{
		m_moveDirection = glm::vec2(1, 0);
	}

	randomNumber = rand() % 2 ;
	if (randomNumber == 1)
	{
		m_moveDirection *= -1;
	}
}
