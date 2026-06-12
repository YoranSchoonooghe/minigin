#pragma once
#include "Components/Component.h"
#include "Events/Subject.h"
#include <array>
#include <string>

namespace dae
{
	class TextComponent;

	class NameEntryComponent final : public Component
	{
	public:
		explicit NameEntryComponent(GameObject* pOwner);
		~NameEntryComponent() = default;
		NameEntryComponent(const NameEntryComponent& other) = delete;
		NameEntryComponent(NameEntryComponent&& other) = delete;
		NameEntryComponent& operator=(const NameEntryComponent& other) = delete;
		NameEntryComponent& operator=(NameEntryComponent&& other) = delete;

		void NextCharacter();
		void PreviousCharacter();
		void NextSlot();
		void PreviousSlot();

		std::string GetName() const { return std::string(m_characters.begin(), m_characters.end()); }

		Subject* GetSubject() const { return m_pSubject.get(); }

	private:
		void UpdateText();

		std::array<char, 3> m_characters{};
		int m_selectedCharacterIndex{ 0 };
		TextComponent* m_pTextComponent;

		std::unique_ptr<Subject> m_pSubject;
	};
}