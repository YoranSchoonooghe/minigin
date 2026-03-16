#pragma once
#include "Component.h"
#include <memory>
#include <Events/Subject.h>

namespace dae
{
	class HealthComponent final : public Component
	{
	public:
		explicit HealthComponent(GameObject* pOwner, int startHealth);
		~HealthComponent();
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		int GetHealth() const;

		void DoDamage(int damage);
		void Heal(int healing);

		void SetMaxHealth(int maxHealth);

		Subject* OnHealthChanged();

	private:
		int m_health;
		int m_maxHealth;

		std::unique_ptr<Subject> m_onHealthChanged;
	};
}