#pragma once
#include <vector>
#include "Components/BoxColliderComponent.h"
#include <glm/fwd.hpp>

namespace dae
{
	class CollisionSystem final
	{
	public:
		explicit CollisionSystem() = default;
		~CollisionSystem() = default;
		CollisionSystem(const CollisionSystem& other) = delete;
		CollisionSystem(CollisionSystem&& other) = delete;
		CollisionSystem& operator=(const CollisionSystem& other) = delete;
		CollisionSystem& operator=(CollisionSystem&& other) = delete;

		void Register(BoxColliderComponent* pCollider);
		void Unregister(BoxColliderComponent* pCollider);

		void MoveAndSlide(BoxColliderComponent* pCollider, const glm::vec2& displacement);
		bool IsOverlapping(const Rect& firstRect, const Rect& secondRect) const;

	private:
		void MoveOnAxis(BoxColliderComponent* pCollider, const glm::vec2& displacement);
		void ApplyPush(BoxColliderComponent* pMovableCollider, BoxColliderComponent* pFixedCollider, const glm::vec2& displacement);

		std::vector<BoxColliderComponent*> m_pColliders;

	};
}