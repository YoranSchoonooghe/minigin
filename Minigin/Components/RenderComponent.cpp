#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture2D.h"
#include "SceneManager.h"
#include <SDL3/SDL_render.h>
#include "imgui.h"


dae::RenderComponent::RenderComponent(GameObject* pOwner, const std::string& filename, bool isInScreenSpace)
	: Component(pOwner)
	, m_isInScreenSpace{ isInScreenSpace }
{
	if (filename != "")
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
		InitializeSrcRect();
	}
}

void dae::RenderComponent::Render() const
{
	SDL_FRect dstRect;
	const auto& position = GetOwner()->GetWorldPosition();

	dstRect.x = position.x;
	dstRect.y = position.y;
	dstRect.w = m_srcRect.w;
	dstRect.h = m_srcRect.h;

	if (!m_isInScreenSpace)
	{
		const auto& cameraPosition = SceneManager::GetInstance().GetActiveScene()->GetActiveCamera()->GetWorldPosition();

		dstRect.x -= cameraPosition.x;
		dstRect.y -= cameraPosition.y;
	}

	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_srcRect, dstRect);
	}
}

void dae::RenderComponent::RenderUI()
{
	if (ImGui::CollapsingHeader("Render", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::Text("Z-Order");

		ImGui::SameLine();

		ImGui::PushItemWidth(80);
		ImGui::DragInt("##zOrder", &m_zOrder, 0.5f, 0, 7);
		ImGui::PopItemWidth();
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
	InitializeSrcRect();
	SDL_SetTextureScaleMode(m_pTexture->GetSDLTexture(), SDL_SCALEMODE_NEAREST);
}

void dae::RenderComponent::SetSrcRect(int row, int col, float width, float height)
{
	m_srcRect.x = width * col;
	m_srcRect.y = height * row;
	m_srcRect.w = width;
	m_srcRect.h = height;
}

void dae::RenderComponent::InitializeSrcRect()
{
	glm::vec2 tileSize = m_pTexture->GetSize();

	m_srcRect.x = 0;
	m_srcRect.y = 0;
	m_srcRect.w = tileSize.x;
	m_srcRect.h = tileSize.y;
}
