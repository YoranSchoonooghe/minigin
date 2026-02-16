#pragma once
#include "Component.h"

namespace dae
{
	class TextComponent;

	class FPS final : public Component
	{
	public:
		explicit FPS();
		~FPS() = default;
		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;

		void Update(float deltaTime) override;

	private:
		TextComponent* m_pTextComponent = nullptr;
	};
}
