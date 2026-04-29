#include "EnemyBehaviourComponent.h"
#include "GameObject.h"
#include "Components/CharacterControllerComponent.h"
#include "Components/BoxColliderComponent.h"
#include <cassert>

dae::EnemyBehaviourComponent::EnemyBehaviourComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	m_pCharacterController = GetOwner()->GetComponent<CharacterControllerComponent>();

	assert(m_pCharacterController != nullptr && "EnemyBehaviourComponent: GameObject is missing a CharacterControllerComponent");

	//m_pCharacterController->SetSpeed(20.0f);

	auto pBoxCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pBoxCollider != nullptr && "BombermanComponent: GameObject is missing a BoxColliderComponent!");

	m_pBoxColliderComponentSubject = pBoxCollider->GetSubject();
	m_pBoxColliderComponentSubject->AddObserver(this);
}

dae::EnemyBehaviourComponent::~EnemyBehaviourComponent()
{
	if (m_pBoxColliderComponentSubject)
	{
		m_pBoxColliderComponentSubject->RemoveObserver(this);
	}
}

void dae::EnemyBehaviourComponent::Update(float)
{
	m_pCharacterController->SetMoveDirection(m_moveDirection);
}

void dae::EnemyBehaviourComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnColliderHit"):
		m_moveDirection *= -1;
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pBoxColliderComponentSubject = nullptr;
		break;
	}
}
