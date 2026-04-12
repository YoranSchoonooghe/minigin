#include "BombComponent.h"
#include "Events//Subject.h"
#include "Components/BoxColliderComponent.h"
#include "Components/TimerComponent.h"
#include <cassert>

dae::BombComponent::BombComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	const auto& pCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pCollider != nullptr && "BombComponent: GameObject is missing a BoxColliderComponent!");

	m_pColliderComponentSubject = pCollider->GetSubject();
	m_pColliderComponentSubject->AddObserver(this);

	const auto& pTimer = GetOwner()->GetComponent<TimerComponent>();

	assert(pTimer != nullptr && "BombComponent: GameObject is missing a TimerComponent!");

	m_pTimerComponentSubject = pTimer->GetTimerSubject();
	m_pTimerComponentSubject->AddObserver(this);
}

dae::BombComponent::~BombComponent()
{
	if (m_pColliderComponentSubject)
	{
		m_pColliderComponentSubject->RemoveObserver(this);
	}
	if (m_pTimerComponentSubject)
	{
		m_pTimerComponentSubject->RemoveObserver(this);
	}
}

void dae::BombComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTriggerExit"):
	{
		const auto& pCollider = GetOwner()->GetComponent<BoxColliderComponent>();
		pCollider->SetTrigger(false);
	}
		break;
	case make_sdbm_hash("OnTimerFinished"):
		GetOwner()->Destroy();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pColliderComponentSubject = nullptr;
		m_pTimerComponentSubject = nullptr;
		break;
	}
}
