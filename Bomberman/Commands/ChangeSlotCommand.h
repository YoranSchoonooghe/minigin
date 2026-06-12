#pragma once
#include "Components/NameEntryComponent.h"
#include <cassert>

namespace dae
{
	class ChangeSlotCommand final : public Command
	{
	public:
		explicit ChangeSlotCommand(GameObject* pGameObject)
		{
			m_pNameEntryComponent = pGameObject->GetComponent<NameEntryComponent>();
			assert(m_pNameEntryComponent != nullptr && "ChangeSlotCommand: GameObject is missing a NameEntryComponent!");
		}

		void Execute() override
		{
			m_pNameEntryComponent->NextSlot();
		}

	private:
		NameEntryComponent* m_pNameEntryComponent;
	};

}