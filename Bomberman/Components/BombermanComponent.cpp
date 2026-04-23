#include "BombermanComponent.h"
#include "Components/BoxColliderComponent.h"
#include <cassert>
#include "GameObject.h"
#include "EnemyBehaviourComponent.h"

dae::BombermanComponent::BombermanComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	auto pBoxCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pBoxCollider != nullptr && "BombermanComponent: GameObject is missing a BoxColliderComponent!");

	m_pBoxColliderComponentSubject = pBoxCollider->GetSubject();
	m_pBoxColliderComponentSubject->AddObserver(this);
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
			GetOwner()->SetLocalPosition(64, 288);
		}
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pBoxColliderComponentSubject = nullptr;
		break;
	}
}
