#include "ExplosionComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/TimerComponent.h"
#include "Components/CharacterControllerComponent.h"
#include "SceneManager.h"
#include "Utils.h"

dae::ExplosionComponent::ExplosionComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	const auto& pCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pCollider != nullptr && "ExplosionComponent: GameObject is missing a BoxColliderComponent!");

	m_pColliderComponentSubject = pCollider->GetSubject();
	m_pColliderComponentSubject->AddObserver(this);

	const auto& pTimer = GetOwner()->GetComponent<TimerComponent>();

	assert(pTimer != nullptr && "ExplosionComponent: GameObject is missing a TimerComponent!");

	m_pTimerComponentSubject = pTimer->GetTimerSubject();
	m_pTimerComponentSubject->AddObserver(this);

	KillOverlappingActors();
}

dae::ExplosionComponent::~ExplosionComponent()
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

void dae::ExplosionComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTriggerEnter"):
	{
		if (pGameObject->GetComponent<dae::BoxColliderComponent>()->GetLayer() & static_cast<uint8_t>(CollisionUtils::Layer::Level))
		{
			GetOwner()->Destroy();
			return;
		}

		pGameObject->Destroy();
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

void dae::ExplosionComponent::KillOverlappingActors() const
{
	const auto& pCollider = GetOwner()->GetComponent<BoxColliderComponent>();
	assert(pCollider != nullptr && "ExplosionComponent: GameObject is missing a BoxColliderComponent!");

	auto pOverlappingGameObjects = SceneManager::GetInstance().GetActiveScene()->GetCollisionSystem()->GetOverlappingColliders(pCollider);

	for (auto* pGameObject : pOverlappingGameObjects)
	{
		if (pGameObject->GetComponent<dae::BoxColliderComponent>()->GetLayer() & static_cast<uint8_t>(CollisionUtils::Layer::Level))
		{
			GetOwner()->Destroy();
			return;
		}

		pGameObject->Destroy();

		if (pGameObject->GetComponent<dae::BoxColliderComponent>()->GetLayer() & static_cast<uint8_t>(CollisionUtils::Layer::Brick))
		{
			GetOwner()->Destroy();
		}
	}
}
