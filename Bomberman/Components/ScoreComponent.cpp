#include "ScoreComponent.h"
#include "Events/Event.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner, int startScore)
	: Component{ pOwner }
	, m_score{ startScore }
{
	m_onScoreChanged = std::make_unique<Subject>();
}

dae::ScoreComponent::~ScoreComponent()
{
	m_onScoreChanged->NotifyObservers(Event(make_sdbm_hash("OnSubjectDestroyed")), GetOwner());
}

void dae::ScoreComponent::AddPoints(int points)
{
	m_score += points;

	m_onScoreChanged->NotifyObservers(Event(make_sdbm_hash("OnScoreChanged")), GetOwner());
}

int dae::ScoreComponent::GetScore() const
{
	return m_score;
}

dae::Subject* dae::ScoreComponent::OnScoreChanged()
{
	return m_onScoreChanged.get();
}
