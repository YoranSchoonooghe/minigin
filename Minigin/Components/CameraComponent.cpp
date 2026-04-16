#include "CameraComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <algorithm>

dae::CameraComponent::CameraComponent(GameObject* pOwner, GameObject* pTarget, SDL_FRect levelBounds, const glm::vec2& targetOffset)
	: Component{ pOwner }
	, m_pTarget{ pTarget }, m_levelBounds{ levelBounds }, m_targetOffset{ targetOffset }
{
	auto* pRenderer = Renderer::GetInstance().GetSDLRenderer();
	SDL_GetRenderOutputSize(pRenderer, &m_width, &m_height);
}

void dae::CameraComponent::Update(float)
{
	glm::vec2 cameraPosition{ m_pTarget->GetWorldPosition() };

	cameraPosition.x += m_targetOffset.x - m_width / 2.0f;
	cameraPosition.y += m_targetOffset.y - m_height / 2.0f;

	cameraPosition.x = std::clamp(cameraPosition.x, m_levelBounds.x, m_levelBounds.w - m_width);
	cameraPosition.y = std::clamp(cameraPosition.y, m_levelBounds.y, m_levelBounds.h - m_height);

	GetOwner()->SetLocalPosition(cameraPosition.x, cameraPosition.y, 0.0f);
}
