#include "BombermanComponent.h"
#include "Components/BoxColliderComponent.h"
#include <cassert>
#include "GameObject.h"
#include "EnemyBehaviourComponent.h"
#include "Audio/ServiceLocator.h"
#include "HealthComponent.h"
#include "GameManager.h"
#include "Utils.h"

dae::BombermanComponent::BombermanComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	auto pBoxCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pBoxCollider != nullptr && "BombermanComponent: GameObject is missing a BoxColliderComponent!");

	m_pBoxColliderComponentSubject = pBoxCollider->GetSubject();
	m_pBoxColliderComponentSubject->AddObserver(this);

	m_pHealthComponent = GetOwner()->GetComponent<HealthComponent>();
	assert(m_pHealthComponent != nullptr && "BombermanComponent: GameObject is missing a HealthComponent!");

	m_pHealthComponentSubject = m_pHealthComponent->GetSubject();
	m_pHealthComponentSubject->AddObserver(this);
}

dae::BombermanComponent::~BombermanComponent()
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

void dae::BombermanComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTriggerEnter"):
		if (auto* pOtherCollider = pGameObject->GetComponent<BoxColliderComponent>())
		{
			if (!(pOtherCollider->GetLayer() & static_cast<uint8_t>(CollisionUtils::Layer::Enemy))
				&& !(pOtherCollider->GetLayer() & static_cast<uint8_t>(CollisionUtils::Layer::Explosion)))
				return;

			m_pHealthComponent->DoDamage(1);
		}
		break;
	case make_sdbm_hash("OnDied"):
		ServiceLocator::GetSoundSystem().Play(1);
		GetOwner()->SetActive(false);
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pBoxColliderComponentSubject = nullptr;
		m_pHealthComponentSubject = nullptr;
		break;
	}
}
