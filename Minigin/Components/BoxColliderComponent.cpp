#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Editor.h"
#include "SceneManager.h"


dae::BoxColliderComponent::BoxColliderComponent(GameObject* pOwner, float width, float height, const glm::vec2& offset, bool isTrigger)
	: Component{ pOwner }
	, m_width{ width }, m_height{ height }, m_offset{ offset }, m_isTrigger{ isTrigger }
{
	SceneManager::GetInstance().GetActiveScene()->GetCollisionSystem()->Register(this);
}

dae::BoxColliderComponent::~BoxColliderComponent()
{
	// STILL NEED TO FIX THIS
	//SceneManager::GetInstance().GetActiveScene()->GetCollisionSystem()->Unregister(this);
}

void dae::BoxColliderComponent::Render() const
{
	if (!Editor::GetInstance().IsDrawCollisionShapesEnabled()) return;

	const auto& worldPosition = GetOwner()->GetWorldPosition();

	SDL_Color debugColor = { 0, 255, 255, 150 };

	Renderer::GetInstance().RenderRect(worldPosition.x + m_offset.x, worldPosition.y + m_offset.y, m_width, m_height, debugColor);
}

dae::Rect dae::BoxColliderComponent::GetCollider() const
{
	const auto& worldPosition = GetOwner()->GetWorldPosition();

	Rect collider{};

	collider.left = worldPosition.x + m_offset.x;
	collider.bottom = worldPosition.y + m_offset.y;
	collider.width = m_width;
	collider.height = m_height;

	return collider;
}
