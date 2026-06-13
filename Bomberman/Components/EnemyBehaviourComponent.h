#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"

namespace dae
{
	class CharacterControllerComponent;
	class AnimationControllerComponent;
	class TimerComponent;
	class Subject;

	class EnemyBehaviourComponent final : public Component, public Observer
	{
	public:
		explicit EnemyBehaviourComponent(GameObject* pOwner, int score);
		~EnemyBehaviourComponent();
		EnemyBehaviourComponent(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent(EnemyBehaviourComponent&& other) = delete;
		EnemyBehaviourComponent& operator=(const EnemyBehaviourComponent& other) = delete;
		EnemyBehaviourComponent& operator=(EnemyBehaviourComponent&& other) = delete;

		void Update(float deltaTime) override;

		void Notify(const Event& event, GameObject* pGameObject) override;

		int GetScore() const { return m_score; }

	private:
		void RandomizeMoveDirection();

		CharacterControllerComponent* m_pCharacterController{};
		AnimationControllerComponent* m_pAnimationController{};
		TimerComponent* m_pDespawnTimer{};
		Subject* m_pBoxColliderComponentSubject{};
		Subject* m_pHealthComponentSubject{};
		Subject* m_pTimerComponentSubject{};

		glm::vec2 m_moveDirection{ -1, 0 };
		bool m_isDead{ false };
		int m_score;
	};
}