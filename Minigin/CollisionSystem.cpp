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

std::vector<dae::GameObject*> dae::CollisionSystem::GetOverlappingColliders(BoxColliderComponent* pCollider)
{
	std::vector<GameObject*> pOverlappingGameObjects{};

	for (const auto& pCol : m_pColliders)
	{
		if (!pCol->GetGameObject()->IsActive()) continue;
		if (!(pCollider->GetMask() & pCol->GetLayer()) || !(pCollider->GetLayer() & pCol->GetMask())) continue;
		if (pCollider == pCol) continue;

		if (IsOverlapping(pCollider->GetCollider(), pCol->GetCollider()))
		{
			pOverlappingGameObjects.push_back(pCol->GetGameObject());
		}
	}

	return pOverlappingGameObjects;
}

void dae::CollisionSystem::MoveAndSlide(BoxColliderComponent* pCollider, const glm::vec2& displacement)
{
	if (displacement.x * displacement.x > FLT_EPSILON)
	{
		MoveOnAxis(pCollider, { displacement.x, 0.0f });
	}
	if (displacement.y * displacement.y > FLT_EPSILON)
	{
		MoveOnAxis(pCollider, { 0.0f, displacement.y });
	}
}

bool dae::CollisionSystem::IsOverlapping(const Rect& firstRect, const Rect& secondRect) const
{
	if ((firstRect.left + firstRect.width) < secondRect.left || firstRect.left > (secondRect.left + secondRect.width))
	{
		return false;
	}
	if ((firstRect.top + firstRect.height) < secondRect.top || firstRect.top > (secondRect.top + secondRect.height))
	{
		return false;
	}

	return true;
}

void dae::CollisionSystem::MoveOnAxis(BoxColliderComponent* pCollider, const glm::vec2& displacement)
{
	Rect predictedCollider{ pCollider->GetCollider() };
	predictedCollider.left += displacement.x;
	predictedCollider.top += displacement.y;

	BoxColliderComponent* pHitCollider{ nullptr };
	for (const auto& pCol : m_pColliders)
	{
		if (!pCol->GetGameObject()->IsActive()) continue;
		if (!(pCollider->GetMask() & pCol->GetLayer()) || !(pCollider->GetLayer() & pCol->GetMask())) continue;
		if (pCollider == pCol) continue;

		if (pCol->IsTrigger())
		{
			if (IsOverlapping(predictedCollider, pCol->GetCollider()))
			{
				pCol->AddOverlappingGameObject(pCollider->GetGameObject());
			}
			else if (IsOverlapping(pCollider->GetCollider(), pCol->GetCollider()))
			{
				pCol->RemoveOverlappingGameObject(pCollider->GetGameObject());
			}

			continue;
		}

		if (IsOverlapping(predictedCollider, pCol->GetCollider()))
		{
			pHitCollider = pCol;
			pCollider->Hit(pCol->GetGameObject());

			break;
		}
	}

	if (!pHitCollider)
	{
		auto position = pCollider->GetGameObject()->GetLocalPosition();
		pCollider->GetGameObject()->SetLocalPosition(position.x + displacement.x, position.y + displacement.y);
	}
	else
	{
		ApplyPush(pCollider, pHitCollider, displacement);
	}
}

void dae::CollisionSystem::ApplyPush(BoxColliderComponent* pMovableCollider, BoxColliderComponent* pFixedCollider, const glm::vec2& displacement)
{
	const float offsetThreshold{ pMovableCollider->GetPushThreshold() };
	if (offsetThreshold < FLT_EPSILON) return;

	const float pushValue{ pMovableCollider->GetPushValue() };

	const auto& movableCollider{ pMovableCollider->GetCollider() };
	const auto& fixedCollider{ pFixedCollider->GetCollider() };

	if (displacement.x * displacement.x > FLT_EPSILON)
	{
		const float distanceFromTop{ (movableCollider.top + movableCollider.height) - fixedCollider.top };
		if (distanceFromTop > 0.0f && distanceFromTop < offsetThreshold)
		{
			const auto& position = pMovableCollider->GetGameObject()->GetLocalPosition();
			pMovableCollider->GetGameObject()->SetLocalPosition(position.x, position.y - pushValue);
		}

		const float distanceFromBottom{ (fixedCollider.top + fixedCollider.height) - movableCollider.top };
		if (distanceFromBottom > 0.0f && distanceFromBottom < offsetThreshold)
		{
			const auto& position = pMovableCollider->GetGameObject()->GetLocalPosition();
			pMovableCollider->GetGameObject()->SetLocalPosition(position.x, position.y + pushValue);
		}
	}

	if (displacement.y * displacement.y > FLT_EPSILON)
	{
		const float distanceFromLeft{ (movableCollider.left + movableCollider.width) - fixedCollider.left };
		if (distanceFromLeft > 0.0f && distanceFromLeft < offsetThreshold)
		{
			const auto& position = pMovableCollider->GetGameObject()->GetLocalPosition();
			pMovableCollider->GetGameObject()->SetLocalPosition(position.x - pushValue, position.y);
		}

		const float distanceFromRight{ (fixedCollider.left + fixedCollider.width) - movableCollider.left };
		if (distanceFromRight > 0.0f && distanceFromRight < offsetThreshold)
		{
			const auto& position = pMovableCollider->GetGameObject()->GetLocalPosition();
			pMovableCollider->GetGameObject()->SetLocalPosition(position.x + pushValue, position.y);
		}
	}
}
