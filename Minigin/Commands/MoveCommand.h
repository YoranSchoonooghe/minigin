#pragma once
#include "Command.h"
#include "GameObject.h"
#include "CharacterControllerComponent.h"
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
			if (!m_pCharacterController)
			{
				m_pCharacterController = pGameObject->GetComponent<dae::CharacterControllerComponent>();
			}

			assert(m_pCharacterController != nullptr && "MoveCommand: GameObject is missing a CharacterControllerComponent!");
		}

		void Execute() override
		{
			m_pCharacterController->SetMoveDirection(m_direction);
		}

	private:
		CharacterControllerComponent* m_pCharacterController = nullptr;

		glm::vec2 m_direction;
	};
}