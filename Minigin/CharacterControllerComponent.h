#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class CharacterControllerComponent final : public Component
	{
	public:
		explicit CharacterControllerComponent(GameObject* pOwner, float speed = 10.0f);
		~CharacterControllerComponent() = default;
		CharacterControllerComponent(const CharacterControllerComponent& other) = delete;
		CharacterControllerComponent(CharacterControllerComponent&& other) = delete;
		CharacterControllerComponent& operator=(const CharacterControllerComponent& other) = delete;
		CharacterControllerComponent& operator=(CharacterControllerComponent&& other) = delete;

		void Update(float deltaTime) override;

		void SetSpeed(float speed);
		void SetMoveDirection(const glm::vec2& direction);

	private:
		float m_speed = 0;
		glm::vec2 m_moveDirection = { 0, 0 };
	};
}