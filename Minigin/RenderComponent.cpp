#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

dae::RenderComponent::RenderComponent(const std::string& filename)
	: m_pTexture{ ResourceManager::GetInstance().LoadTexture(filename) }
{
}

void dae::RenderComponent::Render() const
{
	const auto& pos = owner->GetTransform().GetPosition();

	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}
