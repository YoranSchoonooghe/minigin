#pragma once
#include "Command.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include <cassert>

namespace dae
{
	class DamageCommand : public Command
	{
	public:
		explicit DamageCommand(GameObject* pGameObject, int damage = 1)
			: m_damage{ damage }
		{
			m_pHealthComponent = pGameObject->GetComponent<HealthComponent>();

			assert(m_pHealthComponent != nullptr && "DamageCommand: GameObject is missing a HealthComponent!");
		}

		void Execute() override
		{
			m_pHealthComponent->DoDamage(m_damage);
		}

	private:
		HealthComponent* m_pHealthComponent = nullptr;
		int m_damage;
	};
}