#pragma once
#include "Components/Component.h"
#include <glm/glm.hpp>
#include <Events/Subject.h>
#include <memory>

namespace dae
{
	class BoxColliderComponent;

	class CharacterControllerComponent final : public Component
	{
	public:
		explicit CharacterControllerComponent(GameObject* pOwner, float speed = 10.0f);
		~CharacterControllerComponent();
		CharacterControllerComponent(const CharacterControllerComponent& other) = delete;
		CharacterControllerComponent(CharacterControllerComponent&& other) = delete;
		CharacterControllerComponent& operator=(const CharacterControllerComponent& other) = delete;
		CharacterControllerComponent& operator=(CharacterControllerComponent&& other) = delete;

		void Update(float deltaTime) override;

		void SetSpeed(float speed);
		void SetMoveDirection(const glm::vec2& direction);
		void MoveAndSlide(const glm::vec2& displacement);

		Subject* GetSubject() const { return m_pSubject.get(); };

	private:
		bool IsMoving() const;
		void SendEvents(bool isMoving);

		float m_speed = 0;
		glm::vec2 m_moveDirection = { 0, 0 };
		bool m_wasMovingLastFrame = false;

		BoxColliderComponent* m_pCollider = nullptr;
		bool m_checkedForCollider = false;

		std::unique_ptr<Subject> m_pSubject;
	};
}