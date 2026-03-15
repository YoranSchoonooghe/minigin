#pragma once
#include <string>
#include <memory>
#include "Component.h"
#include <SDL3/SDL_rect.h>

namespace dae
{
	class Texture2D;

	class RenderComponent final : public Component
	{
	public:
		explicit RenderComponent(GameObject* pOwner, const std::string& filename = "");
		~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void Render() const override;

		void SetTexture(std::shared_ptr<Texture2D> pTexture);
		void SetSrcRect(int row, int col, float width, float height);

	private:
		void InitializeSrcRect();

		std::shared_ptr<Texture2D> m_pTexture = nullptr;
		SDL_FRect m_srcRect{};
	};
}