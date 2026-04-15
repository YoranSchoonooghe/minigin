#pragma once
#include "Command.h"
#include "GameObject.h"
#include "CharacterControllerComponent.h"
#include "Components/AnimationControllerComponent.h"
#include <glm/glm.hpp>
#include <cassert>

namespace dae
{
	class MoveCommand : public Command
	{
	public:
		explicit MoveCommand(GameObject* pGameObject, const glm::vec2& direction)
			: m_direction{ direction }
		{
			m_pCharacterController = pGameObject->GetComponent<dae::CharacterControllerComponent>();

			assert(m_pCharacterController != nullptr && "MoveCommand: GameObject is missing a CharacterControllerComponent!");

			m_pAnimationController = pGameObject->GetComponent<dae::AnimationControllerComponent>();
		}

		void Execute() override
		{
			m_pCharacterController->SetMoveDirection(m_direction);

			if (m_pAnimationController)
			{
				m_pAnimationController->UpdateDirection(m_direction);
			}
		}

	private:
		CharacterControllerComponent* m_pCharacterController = nullptr;
		AnimationControllerComponent* m_pAnimationController = nullptr;

		glm::vec2 m_direction;
	};
}