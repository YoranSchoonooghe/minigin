#pragma once
#include "Component.h"
#include "Events/Observer.h"

namespace dae
{
	class Subject;

	class PowerUpComponent final : public Component, public Observer
	{
	public:
		enum class Type
		{
			Flames = 1,
			ExtraBomb = 0,
			Detonator = 4
		};

		explicit PowerUpComponent(GameObject* pOwner, Type type);
		~PowerUpComponent();
		PowerUpComponent(const PowerUpComponent& other) = delete;
		PowerUpComponent(PowerUpComponent&& other) = delete;
		PowerUpComponent& operator=(const PowerUpComponent& other) = delete;
		PowerUpComponent& operator=(PowerUpComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		Type m_type;

		Subject* m_pColliderComponentSubject{ nullptr };
	};
}