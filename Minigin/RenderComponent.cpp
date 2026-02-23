#include "RenderComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Transform.h"

dae::RenderComponent::RenderComponent(GameObject* pOwner, const std::string& filename)
	: Component(pOwner)
{
	if (filename != "")
	{
		m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
	}
}

void dae::RenderComponent::Render() const
{
	const auto& position = GetOwner()->GetWorldPosition();

	if (m_pTexture != nullptr)
	{
		Renderer::GetInstance().RenderTexture(*m_pTexture, position.x, position.y);
	}
}

void dae::RenderComponent::SetTexture(std::shared_ptr<Texture2D> pTexture)
{
	m_pTexture = pTexture;
}