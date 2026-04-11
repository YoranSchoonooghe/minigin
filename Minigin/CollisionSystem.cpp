#include "CollisionSystem.h"
#include "CollisionSystem.h"
#include "GameObject.h"

void dae::CollisionSystem::Register(BoxColliderComponent* pCollider)
{
	m_pColliders.push_back(pCollider);
}

void dae::CollisionSystem::Unregister(BoxColliderComponent* pCollider)
{
	std::erase(m_pColliders, pCollider);
}

void dae::CollisionSystem::Sweep(BoxColliderComponent* pCollider)
{
	for (const auto& pCol : m_pColliders)
	{
		if (!(pCollider == pCol))
		{

		}
	}
}

void dae::CollisionSystem::MoveAndSlide(BoxColliderComponent* pCollider, const glm::vec2& displacement)
{
	auto position = pCollider->GetGameObject()->GetWorldPosition();

	position.x += displacement.x;
	position.y += displacement.y;

	Rect predictedCollider{ pCollider->GetCollider() };
	predictedCollider.left += displacement.x;
	predictedCollider.bottom += displacement.y;

	for (const auto& pCol : m_pColliders)
	{
		if (pCollider == pCol) continue;

		if (IsOverlapping(predictedCollider, pCol->GetCollider())) return;
	}

	auto localPosition{ pCollider->GetGameObject()->GetLocalPosition() };
	pCollider->GetGameObject()->SetLocalPosition(localPosition.x + displacement.x, localPosition.y + displacement.y);
}

bool dae::CollisionSystem::IsOverlapping(const Rect& firstRect, const Rect& secondRect) const
{
	if ((firstRect.left + firstRect.width) < secondRect.left || firstRect.left > (secondRect.left + secondRect.width))
	{
		return false;
	}
	if ((firstRect.bottom + firstRect.height) < secondRect.bottom || firstRect.bottom > (secondRect.bottom + secondRect.height))
	{
		return false;
	}

	return true;
}
