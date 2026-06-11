#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"

namespace dae
{
	class HealthComponent;
	class TimerComponent;
	class Subject;

	class RespawnComponent final : public Component, public Observer
	{
	public:
		explicit RespawnComponent(GameObject* pOwner, HealthComponent* pHealthComponent);
		~RespawnComponent();
		RespawnComponent(const RespawnComponent& other) = delete;
		RespawnComponent(RespawnComponent&& other) = delete;
		RespawnComponent& operator=(const RespawnComponent& other) = delete;
		RespawnComponent& operator=(RespawnComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		TimerComponent* m_pTimerComponent{ nullptr };

		Subject* m_pTimerComponentSubject{};
		Subject* m_pHealthComponentSubject{};

	};
}