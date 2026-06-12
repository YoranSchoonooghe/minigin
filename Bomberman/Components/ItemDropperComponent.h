#pragma once
#include "Components/Component.h"

namespace dae
{
	class ItemDropperComponent final : public Component
	{
	public:
		explicit ItemDropperComponent(GameObject* pOwner, GameObject* pItemToDrop);
		~ItemDropperComponent() = default;
		ItemDropperComponent(const ItemDropperComponent& other) = delete;
		ItemDropperComponent(ItemDropperComponent&& other) = delete;
		ItemDropperComponent& operator=(const ItemDropperComponent& other) = delete;
		ItemDropperComponent& operator=(ItemDropperComponent&& other) = delete;

		void Drop();

	private:
		GameObject* m_pItemToDrop{ nullptr };
	};
}