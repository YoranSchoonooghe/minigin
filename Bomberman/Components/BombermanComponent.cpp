#include "BombermanComponent.h"
#include "Components/BoxColliderComponent.h"
#include <cassert>
#include "GameObject.h"
#include "EnemyBehaviourComponent.h"
#include "Audio/ServiceLocator.h"
#include "HealthComponent.h"

dae::BombermanComponent::BombermanComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	auto pBoxCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pBoxCollider != nullptr && "BombermanComponent: GameObject is missing a BoxColliderComponent!");

	m_pBoxColliderComponentSubject = pBoxCollider->GetSubject();
	m_pBoxColliderComponentSubject->AddObserver(this);

	m_pHealthComponent = GetOwner()->GetComponent<HealthComponent>();
}

dae::BombermanComponent::~BombermanComponent()
{
	if (m_pBoxColliderComponentSubject)
	{
		m_pBoxColliderComponentSubject->RemoveObserver(this);
	}
}

void dae::BombermanComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTriggerEnter"):
		if (pGameObject->GetComponent<EnemyBehaviourComponent>())
		{
			ServiceLocator::GetSoundSystem().Play(1);

			GetOwner()->SetLocalPosition(64, 288);

			auto pBoxCollider = GetOwner()->GetComponent<BoxColliderComponent>();
			pBoxCollider->RemoveOverlappingGameObject(pGameObject);

			if (m_pHealthComponent)
			{
				m_pHealthComponent->DoDamage(1);
			}
		}
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pBoxColliderComponentSubject = nullptr;
		break;
	}
}
