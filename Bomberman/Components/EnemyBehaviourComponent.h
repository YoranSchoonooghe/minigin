#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"

namespace dae
{
	class CharacterControllerComponent;
	class AnimationControllerComponent;
	class Subject;

	class EnemyBehaviourComponent final : public Component, public Observer
	{
	public:
		explicit EnemyBehaviourComponent(GameObject* pOwner);
		~EnemyBehaviourComponent();
		EnemyBehaviourComponent(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent(EnemyBehaviourComponent&& other) = delete;
		EnemyBehaviourComponent& operator=(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent& operator=(EnemyBehaviourComponent&& other) = delete;

		void Update(float deltaTime) override;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void RandomizeMoveDirection();

		CharacterControllerComponent* m_pCharacterController{};
		AnimationControllerComponent* m_pAnimationController{};
		Subject* m_pBoxColliderComponentSubject{};

		glm::vec2 m_moveDirection{ -1, 0 };
	};
}