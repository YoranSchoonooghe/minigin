#include "AnimatedSpriteComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "RenderComponent.h"
#include <cassert>

dae::AnimatedSpriteComponent::AnimatedSpriteComponent(GameObject* pOwner, const std::string& filename, int cols, float frameTime, float tileSize)
	: Component{pOwner}
	, m_cols{ cols }, m_frameTime{ frameTime }, m_tileSize{ tileSize }
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::AnimatedSpriteComponent::Update(float deltaTime)
{
	if (!m_pRenderComponent)
	{
		InitializeRenderComponent();
	}

	m_accumulatedTime += deltaTime;

	if (m_accumulatedTime >= m_frameTime)
	{
		m_currentCol += 1;
		m_currentCol %= m_cols;

		m_accumulatedTime = 0.0f;

		m_pRenderComponent->SetSrcRect(0, m_currentCol, m_tileSize, m_tileSize);
	}
}

void dae::AnimatedSpriteComponent::InitializeRenderComponent()
{
	m_pRenderComponent = GetOwner()->GetComponent<dae::RenderComponent>();

	assert(m_pRenderComponent != nullptr && "AnimatedSpriteComponent: GameObject is missing a RenderComponent!");

	m_pRenderComponent->SetTexture(m_pTexture);
}
