#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPSComponent final : public Component
	{
	public:
		explicit FPSComponent(float updateInterval = 0.4f);
		~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		void Update(float deltaTime) override;

	private:
		float m_updateInterval;
		float m_elapsedUpdateTime;
		TextComponent* m_pTextComponent = nullptr;
	};
}
