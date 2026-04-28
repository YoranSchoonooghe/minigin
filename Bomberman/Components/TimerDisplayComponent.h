#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"
#include <string>

namespace dae
{
	class TextComponent;
	class TimerComponent;
	class Subject;

	class TimerDisplayComponent final : public Component, public Observer
	{
	public:
		explicit TimerDisplayComponent(GameObject* pOwner, GameObject* pTimerOwner, const std::string& label = "Time:");
		~TimerDisplayComponent();
		TimerDisplayComponent(const TimerDisplayComponent& other) = delete;
		TimerDisplayComponent(TimerDisplayComponent&& other) = delete;
		TimerDisplayComponent& operator=(const TimerDisplayComponent& other) = delete;
		TimerDisplayComponent& operator=(TimerDisplayComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void UpdateDisplayText();

		TextComponent* m_pTextComponent = nullptr;
		TimerComponent* m_pTimerComponent = nullptr;
		Subject* m_pTimerComponentSubject = nullptr;
		int m_timeLeft = 0;
		std::string m_label;
	};
}