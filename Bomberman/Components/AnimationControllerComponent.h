#pragma once
#include "Components/Component.h"
#include <glm/fwd.hpp>
#include "Events/Observer.h"

namespace dae
{
	struct SpritesheetMoveDirection
	{
		int left;
		int right;
		int up;
		int down;
	};

	class AnimatedSpriteComponent;
	class CharacterControllerComponent;
	class HealthComponent;
	class Subject;

	class AnimationControllerComponent final : public Component, public Observer
	{
	public:
		explicit AnimationControllerComponent(GameObject* pOwner, const SpritesheetMoveDirection& animationDirection, int deathRow = -1, bool moveWhenIdle = false);
		~AnimationControllerComponent();
		AnimationControllerComponent(const AnimationControllerComponent& other) = delete;
		AnimationControllerComponent(AnimationControllerComponent&& other) = delete;
		AnimationControllerComponent& operator=(const AnimationControllerComponent& other) = delete;
		AnimationControllerComponent& operator=(AnimationControllerComponent&& other) = delete;

		void UpdateDirection(const glm::vec2& moveDirection);

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		SpritesheetMoveDirection m_animationDirection;
		AnimatedSpriteComponent* m_pAnimatedSpriteComponent = nullptr;

		int m_deathAnimationRow;
		bool m_moveWhenIdle;
		Subject* m_pCharacterControllerComponentSubject = nullptr;
		Subject* m_pHealthComponentSubject = nullptr;
	};
}