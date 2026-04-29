#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"

namespace dae
{
	class Subject;

	class BombComponent final : public Component, public Observer
	{
	public:
		explicit BombComponent(GameObject* pOwner);
		~BombComponent();
		BombComponent(const BombComponent& other) = delete;
		BombComponent(BombComponent&& other) = delete;
		BombComponent& operator=(const BombComponent& other) = delete;
		BombComponent& operator=(BombComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;

		void Explode();

	private:
		Subject* m_pColliderComponentSubject = nullptr;
		Subject* m_pTimerComponentSubject = nullptr;
	};
}