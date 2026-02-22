#pragma once
#include <string>
#include <memory>
#include "Component.h"

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

	private:
		std::shared_ptr<Texture2D> m_pTexture = nullptr;
	};
}