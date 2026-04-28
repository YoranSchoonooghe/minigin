#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"

namespace dae
{
	class Subject;

	class BombermanComponent final : public Component, public Observer
	{
	public:
		explicit BombermanComponent(GameObject* pOwner);
		~BombermanComponent();
		BombermanComponent(const BombermanComponent& other) = delete;
		BombermanComponent(BombermanComponent&& other) = delete;
		BombermanComponent& operator=(const BombermanComponent& other) = delete;
		BombermanComponent& operator=(BombermanComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		Subject* m_pBoxColliderComponentSubject = nullptr;

	};
}