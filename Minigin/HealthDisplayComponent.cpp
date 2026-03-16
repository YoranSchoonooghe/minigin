#include "HealthDisplayComponent.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "Events/Subject.h"
#include <string>

dae::HealthDisplayComponent::HealthDisplayComponent(GameObject* pOwner, GameObject* pHealthOwner)
	: Component{ pOwner }
{
	HealthComponent* pHealthComponent = pHealthOwner->GetComponent<HealthComponent>();
	m_pHealthComponentSubject = pHealthComponent->OnHealthChanged();
	m_pHealthComponentSubject->AddObserver(this);

	m_health = pHealthComponent->GetHealth();
}

dae::HealthDisplayComponent::~HealthDisplayComponent()
{
	if (m_pHealthComponentSubject)
	{
		m_pHealthComponentSubject->RemoveObserver(this);
	}
}

void dae::HealthDisplayComponent::Update(float)
{
	if (!m_pTextComponent)
	{
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
		UpdateDisplayText();
	}
}

void dae::HealthDisplayComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnHealthChanged"):
		m_health = pGameObject->GetComponent<HealthComponent>()->GetHealth();
		UpdateDisplayText();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pHealthComponentSubject = nullptr;
		break;
	}
}

void dae::HealthDisplayComponent::UpdateDisplayText()
{
	m_pTextComponent->SetText("Lives: " + std::to_string(m_health));
}
