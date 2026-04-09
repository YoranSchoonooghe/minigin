#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace dae
{
	class BoxColliderComponent final : public Component
	{
	public:
		explicit BoxColliderComponent(GameObject* pOwner, float width, float height, const glm::vec2& offset = {0, 0}, bool isTrigger = false);
		~BoxColliderComponent() = default;
		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;

		void Render() const override;

		bool IsTrigger() const { return m_isTrigger; };

	private:
		float m_width;
		float m_height;
		glm::vec2 m_offset;
		bool m_isTrigger = false;
	};
}