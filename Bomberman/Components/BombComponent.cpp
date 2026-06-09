#include "BombComponent.h"
#include "Events//Subject.h"
#include "Components/BoxColliderComponent.h"
#include "Components/TimerComponent.h"
#include <cassert>
#include "Audio/ServiceLocator.h"
// TEMP
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Components/AnimatedSpriteComponent.h"
#include "Components/ExplosionComponent.h"
#include "Utils.h"
#include "Scene.h"
#include "SceneManager.h"

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

	ServiceLocator::GetSoundSystem().Play(2);
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
		Explode();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pColliderComponentSubject = nullptr;
		m_pTimerComponentSubject = nullptr;
		break;
	}
}

void dae::BombComponent::Explode()
{
	ServiceLocator::GetSoundSystem().Play(3, 2.0f);

	auto pExplosion = std::make_unique<dae::GameObject>("Explosion");
	pExplosion->SetLocalPosition(GetOwner()->GetWorldPosition().x + 64.0f, GetOwner()->GetWorldPosition().y);
	pExplosion->AddComponent<dae::RenderComponent>();
	pExplosion->AddComponent<dae::AnimatedSpriteComponent>("Interactables/Bomb.png", 1, 4, 0.2f, 64.0f);
	auto* pExplosionCollider = pExplosion->AddComponent<dae::BoxColliderComponent>(60.0f, 60.0f, glm::vec2{ 2.0f, 2.0f }, true);
	pExplosionCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Explosion));
	pExplosionCollider->SetMask(0b0001'1111);
	auto pTimer = pExplosion->AddComponent<dae::TimerComponent>(3.0f);
	pExplosion->AddComponent<dae::ExplosionComponent>();
	pTimer->Start();

	auto* pScene = SceneManager::GetInstance().GetActiveScene();
	pScene->Add(std::move(pExplosion));

	GetOwner()->Destroy();
}
