#include "TimerComponent.h"

dae::TimerComponent::TimerComponent(GameObject* pOwner, float duration)
	: Component{ pOwner }
	, m_duration{ duration }
{
	m_timerSubject = std::make_unique<Subject>();
}

dae::TimerComponent::~TimerComponent()
{
	m_timerSubject->NotifyObservers(Event(make_sdbm_hash("OnSubjectDestroyed")), GetOwner());
}

void dae::TimerComponent::Update(float deltaTime)
{
	if (m_isPlaying)
	{
		m_elapsedTime += deltaTime;

		m_timerSubject->NotifyObservers(Event(make_sdbm_hash("OnTimerChanged")), GetOwner());

		if (m_elapsedTime >= m_duration)
		{
			m_isPlaying = false;

			m_timerSubject->NotifyObservers(Event(make_sdbm_hash("OnTimerFinished")), GetOwner());
		}
	}
}

void dae::TimerComponent::Start()
{
	if (m_elapsedTime >= m_duration) return;

	m_isPlaying = true;
}

void dae::TimerComponent::Stop()
{
	m_isPlaying = false;
}

void dae::TimerComponent::Reset()
{
	m_elapsedTime = 0.0f;
}

void dae::TimerComponent::Restart()
{
	Reset();
	Start();
}

float dae::TimerComponent::GetTimeLeft() const
{
	return (m_duration - m_elapsedTime);
}

dae::Subject* dae::TimerComponent::GetTimerSubject() const
{
	return m_timerSubject.get();
}
