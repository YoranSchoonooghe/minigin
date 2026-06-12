#include "NameEntryComponent.h"
#include "Components/TextComponent.h"
#include "GameObject.h"

dae::NameEntryComponent::NameEntryComponent(GameObject* pOwner)
	: Component{ pOwner }
{
	for (auto& character : m_characters)
	{
		character = 'A';
	}

	m_pSubject = std::make_unique<Subject>();

	m_pTextComponent = GetOwner()->GetComponent<TextComponent>();
	assert(m_pTextComponent != nullptr && "NameEntryComponent: GameObject is missing a TextComponent!");

	UpdateText();
}

void dae::NameEntryComponent::NextCharacter()
{
	char& character = m_characters[m_selectedCharacterIndex];

	if (character == 'Z')
	{
		character = 'A';
	}
	else
	{
		character += 1;
	}

	UpdateText();
}

void dae::NameEntryComponent::PreviousCharacter()
{
	char& character = m_characters[m_selectedCharacterIndex];

	if (character == 'A')
	{
		character = 'Z';
	}
	else
	{
		character -= 1;
	}

	UpdateText();
}

void dae::NameEntryComponent::NextSlot()
{
	if (m_selectedCharacterIndex < (static_cast<int>(m_characters.size()) - 1))
	{
		++m_selectedCharacterIndex;
	}
	else
	{
		m_pSubject->NotifyObservers(Event(make_sdbm_hash("OnNameEntered")), GetOwner());
	}
}

void dae::NameEntryComponent::PreviousSlot()
{
	if (m_selectedCharacterIndex > 0)
	{
		--m_selectedCharacterIndex;
	}
}

void dae::NameEntryComponent::UpdateText()
{
	m_pTextComponent->SetText(GetName());
}
