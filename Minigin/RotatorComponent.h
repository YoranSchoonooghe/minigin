#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class RotatorComponent final : public Component
	{
	public:
		explicit RotatorComponent(GameObject* pOwner, float radius, float angularVelocity);
		~RotatorComponent() = default;
		RotatorComponent(const RotatorComponent& other) = delete;
		RotatorComponent(RotatorComponent&& other) = delete;
		RotatorComponent& operator=(const RotatorComponent& other) = delete;
		RotatorComponent& operator=(RotatorComponent&& other) = delete;

		void Update(float deltaTime) override;

	private:
		float WrapAngle(float angle) const;

		float m_radius;
		float m_angularVelocity;
		float m_angle = 0.0f;
	};
}