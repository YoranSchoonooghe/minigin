#pragma once
#include "Commands/Command.h"
#include "GameObject.h"
#include "Scene.h"
#include "Components/BombComponent.h"
#include <cmath>
#include "Utils.h"

namespace dae
{
	class DropBombCommand final : public Command
	{
	public:
		explicit DropBombCommand(GameObject* pGameObject)
			: m_pGameObject{ pGameObject }
		{
		}

		void Execute() override
		{
			auto position{ m_pGameObject->GetWorldPosition() };
			SnapToGrid(position, 64.0f);

			auto pBomb = std::make_unique<dae::GameObject>();
			pBomb->AddComponent<dae::RenderComponent>();
			pBomb->AddComponent<dae::AnimatedSpriteComponent>("Interactables/Bomb.png", 1, 4, 0.2f, 64.0f);
			auto* pBombCollider = pBomb->AddComponent<dae::BoxColliderComponent>(64.0f, 64.0f, glm::vec2{ 0.0f, 0.0f }, true);
			pBombCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Bomb));
			auto pTimer = pBomb->AddComponent<dae::TimerComponent>(3.0f);
			pBomb->AddComponent<dae::BombComponent>();
			pTimer->Start();
			pBomb->SetLocalPosition(position.x, position.y);

			auto pScene = SceneManager::GetInstance().GetActiveScene();
			pScene->Add(std::move(pBomb));
		}

	private:
		void SnapToGrid(glm::vec3& position, float gridSize)
		{
			position.x = std::roundf(position.x / gridSize) * gridSize;
			position.y = std::roundf((position.y - 224.0f) / gridSize) * gridSize + 224.0f;
		}

		GameObject* m_pGameObject;
	};
}