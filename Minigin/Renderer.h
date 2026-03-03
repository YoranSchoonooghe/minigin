#pragma once
#include <SDL3/SDL.h>
#include "Singleton.h"
#include <vector>

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }

	private:
		static std::vector<float> ThrashCache(int samples);
		static std::vector<float> ThrashCacheGameObject(int samples);
		static std::vector<float> ThrashCacheGameObjectAlt(int samples);

		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};

		static int m_samplesExercise1;
		static int m_samplesExercise2;
		static std::vector<float> m_plotDataExercise1;
		static std::vector<float> m_plotDataExercise2;
		static std::vector<float> m_plotDataExercise2Alt;
	};
}

