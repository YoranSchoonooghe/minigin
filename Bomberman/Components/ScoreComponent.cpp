#include "ScoreComponent.h"
#include "Events/Event.h"
#include "Events/EventManager.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner, int startScore)
	: Component{ pOwner }
	, m_score{ startScore }
{
	m_onScoreChanged = std::make_unique<Subject>();

	m_pEventManager = &EventManager::GetInstance();
	m_pEventManager->AddObserver(this);
}

dae::ScoreComponent::~ScoreComponent()
{
	m_onScoreChanged->NotifyObservers(Event(make_sdbm_hash("OnSubjectDestroyed")), GetOwner());

	if (m_pEventManager)
	{
		m_pEventManager->RemoveObserver(this);
	}
}

void dae::ScoreComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnEnemyDied"):
		m_score += 100;
		m_onScoreChanged->NotifyObservers(Event(make_sdbm_hash("OnScoreChanged")), GetOwner());
		break;
	case make_sdbm_hash("OnEventManagerDestroyed"):
		m_pEventManager = nullptr;
		break;
	}
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

dae::Subject* dae::ScoreComponent::GetSubject()
{
	return m_onScoreChanged.get();
}
