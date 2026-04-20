#include "CameraComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include <algorithm>
#include "imgui.h"

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

void dae::CameraComponent::RenderUI()
{
	if (ImGui::CollapsingHeader("Camera", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::PushItemWidth(80);

		ImGui::Text("Target Offset"); ImGui::SameLine();

		ImGui::Text("X"); ImGui::SameLine();
		ImGui::DragFloat("##TargetOffsetX", &m_targetOffset.x, 1.0f, 0.0f, 0.0f, "%.1f");
		ImGui::SameLine();
		ImGui::Text("Y"); ImGui::SameLine();
		ImGui::DragFloat("##TargetOffsetY", &m_targetOffset.y, 1.0f, 0.0f, 0.0f, "%.1f");
		
		ImGui::PopItemWidth();
	}
}
