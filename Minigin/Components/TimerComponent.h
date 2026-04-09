#pragma once
#include "Component.h"
#include <memory>
#include <Events/Subject.h>

namespace dae
{
	class TimerComponent final : public Component
	{
	public:
		explicit TimerComponent(GameObject* pOwner, float duration);
		~TimerComponent();
		TimerComponent(const TimerComponent& other) = delete;
		TimerComponent(TimerComponent&& other) = delete;
		TimerComponent& operator=(const TimerComponent& other) = delete;
		TimerComponent& operator=(TimerComponent&& other) = delete;

		void Update(float deltaTime) override;

		void Start();
		void Stop();
		void Reset();
		void Restart();

		float GetTimeLeft() const;
		Subject* GetTimerSubject() const;

	private:
		float m_elapsedTime = 0.0f;
		float m_duration;
		bool m_isPlaying = false;

		std::unique_ptr<Subject> m_timerSubject;
	};
}