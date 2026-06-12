#pragma once
#include "Components/Component.h"

namespace dae
{
	class ItemDropperComponent;

	class BrickComponent final : public Component
	{
	public:
		explicit BrickComponent(GameObject* pOwner);
		~BrickComponent() = default;
		BrickComponent(const BrickComponent& other) = delete;
		BrickComponent(BrickComponent&& other) = delete;
		BrickComponent& operator=(const BrickComponent& other) = delete;
		BrickComponent& operator=(BrickComponent&& other) = delete;

		void Explode();

	private:
		ItemDropperComponent* m_pItemDropper;
	};
}