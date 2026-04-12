#pragma once
#include "Component.h"
#include "glm/glm.hpp"

namespace dae
{
	class GameObject;

	struct Rect
	{
		float left;
		float top;
		float width;
		float height;
	};

	class BoxColliderComponent final : public Component
	{
	public:
		explicit BoxColliderComponent(GameObject* pOwner, float width, float height, const glm::vec2& offset = {0, 0}, bool isTrigger = false, 
			float pushThreshold = 0.0f, float pushValue = 1.0f);
		~BoxColliderComponent();
		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) = delete;

		void Render() const override;

		bool IsTrigger() const { return m_isTrigger; };
		Rect GetCollider() const;
		GameObject* GetGameObject() const { return GetOwner(); };

		float GetPushThreshold() const { return m_pushThreshold; };
		float GetPushValue() const { return m_pushValue; };

	private:
		float m_width;
		float m_height;
		glm::vec2 m_offset;
		bool m_isTrigger = false;

		float m_pushThreshold;
		float m_pushValue;
	};
}