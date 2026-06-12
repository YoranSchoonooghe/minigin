#pragma once
#include "Components/NameEntryComponent.h"
#include <cassert>

namespace dae
{
	class ChangeCharacterCommand final : public Command
	{
	public:
		explicit ChangeCharacterCommand(GameObject* pGameObject, bool forward = true)
			: m_moveForward{ forward }
		{
			m_pNameEntryComponent = pGameObject->GetComponent<NameEntryComponent>();
			assert(m_pNameEntryComponent != nullptr && "ChangeCharacterCommand: GameObject is missing a NameEntryComponent!");
		}

		void Execute() override
		{
			if (m_moveForward)
				m_pNameEntryComponent->NextCharacter();
			else
				m_pNameEntryComponent->PreviousCharacter();
		}

	private:
		NameEntryComponent* m_pNameEntryComponent;
		bool m_moveForward;
	};

}