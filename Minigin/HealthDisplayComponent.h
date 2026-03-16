#pragma once
#include "Component.h"
#include "Events/Observer.h"

namespace dae
{
	class TextComponent;
	class Subject;

	class HealthDisplayComponent final : public Component, public Observer
	{
	public:
		explicit HealthDisplayComponent(GameObject* pOwner, GameObject* pHealthOwner);
		~HealthDisplayComponent();
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void UpdateDisplayText();

		TextComponent* m_pTextComponent = nullptr;
		Subject* m_pHealthComponentSubject = nullptr;
		int m_health = 0;
	};
}