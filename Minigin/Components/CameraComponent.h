#pragma once
#include "Components/Component.h"
#include <glm/glm.hpp>
#include <SDL3/SDL_rect.h>

namespace dae
{
	class CameraComponent final : public Component
	{
	public:
		explicit CameraComponent(GameObject* pOwner, GameObject* pTarget, SDL_FRect levelBounds, const glm::vec2& offset = {0, 0});
		~CameraComponent() = default;
		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) = delete;

		void Update(float deltaTime) override;
		void RenderUI() override;

	private:
		GameObject* m_pTarget;
		SDL_FRect m_levelBounds;
		glm::vec2 m_targetOffset;

		int m_width;
		int m_height;
	};
}