#include <format>
#include "FPSComponent.h"
#include "TextComponent.h"
#include "GameObject.h"

dae::FPSComponent::FPSComponent(float updateInterval)
	: m_updateInterval{ updateInterval }
	, m_elapsedUpdateTime{ 0.0f }
{
}

void dae::FPSComponent::Update(float deltaTime)
{
	m_elapsedUpdateTime += deltaTime;
	if (m_elapsedUpdateTime <= m_updateInterval) return;

	if (m_pTextComponent == nullptr)
	{
		m_pTextComponent = owner->GetComponent<dae::TextComponent>();
	}

	if (m_pTextComponent)
	{
		const float FPS = 1.0f / deltaTime;
		m_pTextComponent->SetText(std::format("{:.1f} FPS", FPS));
	}

	m_elapsedUpdateTime = 0.0f;
}
