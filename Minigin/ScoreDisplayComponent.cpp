#include "ScoreDisplayComponent.h"
#include "TextComponent.h"
#include "ScoreComponent.h"
#include "Events/Subject.h"
#include <string>

dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* pOwner, GameObject* pScoreOwner)
	: Component{ pOwner }
{
	ScoreComponent* pScoreComponent = pScoreOwner->GetComponent<ScoreComponent>();
	m_pScoreComponentSubject = pScoreComponent->OnScoreChanged();
	m_pScoreComponentSubject->AddObserver(this);

	m_score = pScoreComponent->GetScore();
}

dae::ScoreDisplayComponent::~ScoreDisplayComponent()
{
	if (m_pScoreComponentSubject)
	{
		m_pScoreComponentSubject->RemoveObserver(this);
	}
}

void dae::ScoreDisplayComponent::Update(float)
{
	if (!m_pTextComponent)
	{
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
		UpdateDisplayText();
	}
}

void dae::ScoreDisplayComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnScoreChanged"):
		m_score = pGameObject->GetComponent<ScoreComponent>()->GetScore();
		UpdateDisplayText();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pScoreComponentSubject = nullptr;
		break;
	}
}

void dae::ScoreDisplayComponent::UpdateDisplayText()
{
	m_pTextComponent->SetText("Score: " + std::to_string(m_score));
}
