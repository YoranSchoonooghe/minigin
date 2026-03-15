#pragma once
#include "Component.h"

namespace dae
{
	class HealthComponent final : public Component
	{
	public:
		explicit HealthComponent(GameObject* pOwner, int startHealth);
		~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void DoDamage(int damage);
		void Heal(int healing);

		void SetMaxHealth(int maxHealth);

	private:
		int m_health;
		int m_maxHealth;
	};
}