#include "RespawnComponent.h"
#include "HealthComponent.h"
#include "TimerComponent.h"
#include "GameManager.h"
#include "Events/Subject.h"
#include <cassert>

dae::RespawnComponent::RespawnComponent(GameObject* pOwner, HealthComponent* pHealthComponent)
	: Component{ pOwner }
{
	m_pHealthComponentSubject = pHealthComponent->GetSubject();
	m_pHealthComponentSubject->AddObserver(this);

	m_pTimerComponent = GetOwner()->GetComponent<TimerComponent>();
	assert(m_pTimerComponent != nullptr && "RespawnComponent: GameObject is missing a TimerComponent");

	m_pTimerComponentSubject = m_pTimerComponent->GetTimerSubject();
	m_pTimerComponentSubject->AddObserver(this);
}

dae::RespawnComponent::~RespawnComponent()
{
	if (m_pHealthComponentSubject)
	{
		m_pHealthComponentSubject->RemoveObserver(this);
	}

	if (m_pTimerComponentSubject)
	{
		m_pTimerComponentSubject->RemoveObserver(this);
	}
}

void dae::RespawnComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnDied"):
		m_pTimerComponent->Start();
		break;
	case make_sdbm_hash("OnTimerFinished"):
		GameManager::GetInstance().RestartStage();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		if (pGameObject->GetComponent<HealthComponent>())
		{
			m_pHealthComponentSubject = nullptr;
		}
		else
		{
			m_pTimerComponentSubject = nullptr;
		}
		break;
	}
}
