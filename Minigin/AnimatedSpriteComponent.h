#pragma once
#include "Component.h"
#include <memory>
#include <string>

namespace dae
{
	class Texture2D;
	class RenderComponent;

	class AnimatedSpriteComponent final : public Component
	{
	public:
		explicit AnimatedSpriteComponent(GameObject* pOwner, const std::string& filename, int cols, float frameTime, float tileSize);
		~AnimatedSpriteComponent() = default;
		AnimatedSpriteComponent(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent(AnimatedSpriteComponent&& other) = delete;
		AnimatedSpriteComponent& operator=(const AnimatedSpriteComponent& other) = delete;
		AnimatedSpriteComponent& operator=(AnimatedSpriteComponent&& other) = delete;

		void Update(float deltaTime) override;

	private:
		void InitializeRenderComponent();

		std::shared_ptr<Texture2D> m_pTexture = nullptr;
		int m_cols;
		int m_currentCol = 0;
		float m_frameTime;
		float m_accumulatedTime = 0.0f;
		float m_tileSize;

		RenderComponent* m_pRenderComponent = nullptr;
	};
}