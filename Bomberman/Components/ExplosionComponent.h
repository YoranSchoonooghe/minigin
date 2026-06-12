#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"

namespace dae
{
	class Subject;

	class ExplosionComponent final : public Component, public Observer
	{
	public:
		explicit ExplosionComponent(GameObject* pOwner);
		~ExplosionComponent();
		ExplosionComponent(const ExplosionComponent& other) = delete;
		ExplosionComponent(ExplosionComponent&& other) = delete;
		ExplosionComponent& operator=(const ExplosionComponent& other) = delete;
		ExplosionComponent& operator=(ExplosionComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;
		bool HitBrick() const { return m_hitBrick; }

	private:
		void KillOverlappingActors();

		Subject* m_pColliderComponentSubject = nullptr;
		Subject* m_pTimerComponentSubject = nullptr;
		bool m_hitBrick{ false };
	};
}