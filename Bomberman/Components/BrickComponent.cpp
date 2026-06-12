#include "BrickComponent.h"
#include "ItemDropperComponent.h"
#include "GameObject.h"

dae::BrickComponent::BrickComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	m_pItemDropper = GetOwner()->GetComponent<ItemDropperComponent>();
}

void dae::BrickComponent::Explode()
{
	if (m_pItemDropper)
	{
		m_pItemDropper->Drop();
	}

	GetOwner()->Destroy();
}
