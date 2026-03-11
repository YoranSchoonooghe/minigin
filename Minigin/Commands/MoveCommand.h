#pragma once
#include "Command.h"
#include "GameObject.h"
#include <glm/glm.hpp>

namespace dae
{
	class MoveCommand : public Command
	{
	public:
		explicit MoveCommand(GameObject* pGameObject, float speed, const glm::vec2& direction)
			: m_pGameObject{ pGameObject }, m_speed{ speed }, m_direction{ direction }
		{
		}

		void Execute() override
		{
			const auto& localPosition = m_pGameObject->GetTransform()->GetLocalPosition();

			float xPosition = localPosition.x + m_direction.x * m_speed;
			float yPosition = localPosition.y + m_direction.y * m_speed;

			m_pGameObject->SetLocalPosition(xPosition, yPosition);
		}

	private:
		GameObject* m_pGameObject;

		float m_speed;
		glm::vec2 m_direction;
	};
}