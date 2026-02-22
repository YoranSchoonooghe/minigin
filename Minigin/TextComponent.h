#pragma once
#include <SDL3/SDL_pixels.h>
#include <string>
#include <memory>
#include "Component.h"

namespace dae
{
	class Font;
	class Texture2D;
	class RenderComponent;

	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(GameObject* pOwner, const std::string& text, std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255, 255 });
		~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Update(float deltaTime) override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

	private:
		bool m_needsUpdate = true;
		std::string m_text{};
		SDL_Color m_color{ 255, 255, 255, 255 };
		std::shared_ptr<Font> m_font = nullptr;
		std::shared_ptr<Texture2D> m_pTextTexture = nullptr;

		RenderComponent* m_pRenderComponent = nullptr;
	};
}