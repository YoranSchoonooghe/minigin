#include "TimerDisplayComponent.h"
#include "TimerComponent.h"
#include "TextComponent.h"

dae::TimerDisplayComponent::TimerDisplayComponent(GameObject* pOwner, GameObject* pTimerOwner, const std::string& label)
	: Component{ pOwner }
	, m_label{ label }
{
	m_pTimerComponent = pTimerOwner->GetComponent<TimerComponent>();
	m_pTimerComponentSubject = m_pTimerComponent->GetTimerSubject();
	m_pTimerComponentSubject->AddObserver(this);

	m_timeLeft = static_cast<int>(m_pTimerComponent->GetTimeLeft());
}

dae::TimerDisplayComponent::~TimerDisplayComponent()
{
	if (m_pTimerComponentSubject)
	{
		m_pTimerComponentSubject->RemoveObserver(this);
	}
}

void dae::TimerDisplayComponent::Update(float)
{
	if (!m_pTextComponent)
	{
		m_pTextComponent = GetOwner()->GetComponent<dae::TextComponent>();
		UpdateDisplayText();
	}
}

void dae::TimerDisplayComponent::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTimerChanged"):
	{
		int const TIME_LEFT = static_cast<int>(m_pTimerComponent->GetTimeLeft());
		if (m_timeLeft != TIME_LEFT)
		{
			m_timeLeft = TIME_LEFT;
			UpdateDisplayText();
		}
	}
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pTimerComponentSubject = nullptr;
		break;
	}
}

void dae::TimerDisplayComponent::UpdateDisplayText()
{
	m_pTextComponent->SetText(m_label + " " + std::to_string(m_timeLeft));
}
