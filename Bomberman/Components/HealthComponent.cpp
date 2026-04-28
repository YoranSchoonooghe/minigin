#include "HealthComponent.h"
#include <algorithm>
#include "Events/Event.h"

dae::HealthComponent::HealthComponent(GameObject* pOwner, int startHealth)
	: Component{ pOwner }
	, m_health{ startHealth }, m_maxHealth{ startHealth }
{
	m_onHealthChanged = std::make_unique<Subject>();
}

dae::HealthComponent::~HealthComponent()
{
	m_onHealthChanged->NotifyObservers(Event(make_sdbm_hash("OnSubjectDestroyed")), GetOwner());
}

int dae::HealthComponent::GetHealth() const
{
	return m_health;
}

void dae::HealthComponent::DoDamage(int damage)
{
	m_health = std::max(m_health - damage, 0);

	if (m_health == 0)
	{
		//dispatch event that GameObject died
	}

	m_onHealthChanged->NotifyObservers(Event(make_sdbm_hash("OnHealthChanged")), GetOwner());
}

void dae::HealthComponent::Heal(int healing)
{
	m_health = std::min(m_health + healing, m_maxHealth);

	m_onHealthChanged->NotifyObservers(Event(make_sdbm_hash("OnHealthChanged")), GetOwner());
}

void dae::HealthComponent::SetMaxHealth(int maxHealth)
{
	m_maxHealth = maxHealth;
}

dae::Subject* dae::HealthComponent::OnHealthChanged()
{
	return m_onHealthChanged.get();
}
