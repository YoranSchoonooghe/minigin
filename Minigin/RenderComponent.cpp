#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture2D.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner, const std::string& filename)
	: Component(pOwner)
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

	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, m_srcRect, dstRect);
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
	InitializeSrcRect();
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
