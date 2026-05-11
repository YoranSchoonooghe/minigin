#include "ExitComponent.h"
#include "Components/BoxColliderComponent.h"
#include "GameObject.h"
#include "Components/BombermanComponent.h"
#include "GameManager.h"

dae::ExitComponent::ExitComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	auto pBoxCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pBoxCollider != nullptr && "ExitComponent: GameObject is missing a BoxColliderComponent!");

	m_pBoxColliderComponentSubject = pBoxCollider->GetSubject();
	m_pBoxColliderComponentSubject->AddObserver(this);
}

dae::ExitComponent::~ExitComponent()
{
	if (m_pBoxColliderComponentSubject)
	{
		m_pBoxColliderComponentSubject->RemoveObserver(this);
	}
}

void dae::ExitComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTriggerEnter"):
		if (pGameObject->GetComponent<BombermanComponent>())
		{
			GameManager::GetInstance().ExitStage();
		}
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pBoxColliderComponentSubject = nullptr;
		break;
	}
}
