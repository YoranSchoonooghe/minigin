#include "ItemDropperComponent.h"
#include "GameObject.h"

dae::ItemDropperComponent::ItemDropperComponent(GameObject* pOwner, GameObject* pItemToDrop)
	: Component{ pOwner }
	, m_pItemToDrop{ pItemToDrop }
{}

void dae::ItemDropperComponent::Drop()
{
	m_pItemToDrop->SetActive(true);
}
