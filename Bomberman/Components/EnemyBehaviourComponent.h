#pragma once
#include "Component.h"

namespace dae
{
	class EnemyBehaviourComponent final : public Component
	{
	public:
		explicit EnemyBehaviourComponent(GameObject* pOwner);
		~EnemyBehaviourComponent() = default;
		EnemyBehaviourComponent(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent(EnemyBehaviourComponent&& other) = delete;
		EnemyBehaviourComponent& operator=(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent& operator=(EnemyBehaviourComponent&& other) = delete;

	private:


	};
}