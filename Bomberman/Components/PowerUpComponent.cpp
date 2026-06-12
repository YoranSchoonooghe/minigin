#include "PowerUpComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/RenderComponent.h"
#include "GameManager.h"
#include <cassert>
#include "Audio/ServiceLocator.h"
#include "Events/EventManager.h"

dae::PowerUpComponent::PowerUpComponent(GameObject* pOwner, Type type)
	: Component{ pOwner }
	, m_type{ type }
{
	const auto& pCollider = GetOwner()->GetComponent<BoxColliderComponent>();

	assert(pCollider != nullptr && "PowerUpComponent: GameObject is missing a BoxColliderComponent!");

	m_pColliderComponentSubject = pCollider->GetSubject();
	m_pColliderComponentSubject->AddObserver(this);

	const auto& pRenderComponent = GetOwner()->GetComponent<RenderComponent>();

	assert(pCollider != nullptr && "PowerUpComponent: GameObject is missing a RenderComponent!");

	pRenderComponent->SetSrcRect(0, static_cast<int>(m_type), 64.0f, 64.0f);
}

dae::PowerUpComponent::~PowerUpComponent()
{
	if (m_pColliderComponentSubject)
	{
		m_pColliderComponentSubject->RemoveObserver(this);
	}
}

void dae::PowerUpComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTriggerEnter"):
		PickUp();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pColliderComponentSubject = nullptr;
		break;
	}
}

void dae::PowerUpComponent::PickUp() const
{
	ServiceLocator::GetSoundSystem().Play(4);

	auto powerUpData{ GameManager::GetInstance().GetPowerUpData() };
	switch (m_type)
	{
	case dae::PowerUpComponent::Type::Flames:
		powerUpData.flameRange = std::min(4, powerUpData.flameRange + 1);
		break;
	case dae::PowerUpComponent::Type::ExtraBomb:
		powerUpData.nrOfBombs = std::min(10, powerUpData.nrOfBombs + 1);
		break;
	case dae::PowerUpComponent::Type::Detonator:
		powerUpData.hasDetonator = true;
		break;
	}

	EventManager::GetInstance().SendEvent(Event(make_sdbm_hash("OnItemPickedUp")), GetOwner());

	GameManager::GetInstance().SetPowerUpData(powerUpData);

	//GetOwner()->Destroy();
	GetOwner()->SetActive(false);
}
