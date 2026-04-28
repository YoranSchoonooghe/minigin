#include "PowerUpComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/RenderComponent.h"
#include <cassert>

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
		GetOwner()->Destroy();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pColliderComponentSubject = nullptr;
		break;
	}
}
