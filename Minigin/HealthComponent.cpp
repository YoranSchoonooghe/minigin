#include "HealthComponent.h"
#include <algorithm>

dae::HealthComponent::HealthComponent(GameObject* pOwner, int startHealth)
	: Component{ pOwner }
	, m_health{ startHealth }, m_maxHealth{ startHealth }
{
}

void dae::HealthComponent::DoDamage(int damage)
{
	m_health = std::min(m_health - damage, 0);

	if (m_health == 0)
	{
		//GameObject died
	}

	//dispatch event that damage was taken
}

void dae::HealthComponent::Heal(int healing)
{
	m_health = std::max(m_health + healing, m_maxHealth);

	//dispatch event that GO healed
}

void dae::HealthComponent::SetMaxHealth(int maxHealth)
{
	m_maxHealth = maxHealth;
}
