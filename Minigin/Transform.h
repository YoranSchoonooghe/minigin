#pragma once
#include "Component.h"
#include <glm/glm.hpp>

namespace dae
{
	class Transform final : Component
	{
	public:
		explicit Transform(GameObject* pOwner, const glm::vec3& position = glm::vec3(0, 0, 0) );
		~Transform() = default;
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& GetWorldPosition();
		const glm::vec3& GetLocalPosition() const { return m_localPosition; }
		void SetLocalPosition(float x, float y, float z = 0);
		void SetLocalPosition(const glm::vec3& localPosition);

		void SetPositionDirty();

	private:
		void UpdateWorldPosition();

		glm::vec3 m_worldPosition;
		glm::vec3 m_localPosition;
		bool m_positionIsDirty = false;
	};
}
