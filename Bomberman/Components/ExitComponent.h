#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"

namespace dae
{
	class Subject;

	class ExitComponent final : public Component, public Observer
	{
	public:
		explicit ExitComponent(GameObject* pOwner);
		~ExitComponent();
		ExitComponent(const ExitComponent& other) = delete;
		ExitComponent(ExitComponent&& other) = delete;
		ExitComponent& operator=(const ExitComponent& other) = delete;
		ExitComponent& operator=(ExitComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;

		void OpenSesame() { m_isOpen = true; }

	private:
		Subject* m_pBoxColliderComponentSubject{ nullptr };

		bool m_isOpen{ false };
	};
}