#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Editor.h"

dae::BoxColliderComponent::BoxColliderComponent(GameObject* pOwner, float width, float height, const glm::vec2& offset, bool isTrigger)
	: Component{ pOwner }
	, m_width{ width }, m_height{ height }, m_offset{ offset }, m_isTrigger{ isTrigger }
{
}

void dae::BoxColliderComponent::Render() const
{
	if (!Editor::GetInstance().IsDrawCollisionShapesEnabled()) return;

	const auto& worldPosition = GetOwner()->GetWorldPosition();

	SDL_Color debugColor = { 0, 255, 255, 150 };

	Renderer::GetInstance().RenderRect(worldPosition.x + m_offset.x, worldPosition.y + m_offset.y, m_width, m_height, debugColor);
}
