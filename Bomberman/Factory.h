#pragma once
#include <memory>
#include <string>
#include <iostream>
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Components/AnimatedSpriteComponent.h"
#include "Components/CharacterControllerComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/AnimationControllerComponent.h"
#include "Components/EnemyBehaviourComponent.h"

namespace dae
{
	namespace EnemyFactory
	{
		std::unique_ptr<GameObject> CreateBalloom()
		{
			auto pBalloom = std::make_unique<dae::GameObject>("Balloom");
			pBalloom->AddComponent<dae::RenderComponent>();
			pBalloom->AddComponent<dae::CharacterControllerComponent>(100.0f);
			auto* pBalloomCollider = pBalloom->AddComponent<dae::BoxColliderComponent>(56.0f, 62.0f, glm::vec2{ 4.0f, 1.0f }, true, 20.0f, 2.0f);
			pBalloomCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Enemy));
			pBalloomCollider->SetMask(0b0011'1011);
			pBalloom->AddComponent<dae::AnimatedSpriteComponent>("Characters/Balloom.png", 4, 4, 0.1f, 64.0f, false);
			pBalloom->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 1, 0, 0, 1 });
			pBalloom->AddComponent<dae::EnemyBehaviourComponent>();

			return pBalloom;
		}

		std::unique_ptr<GameObject> CreateEnemy(const std::string& enemyType)
		{
			if (enemyType == "balloom")
				return CreateBalloom();
			else
			{
				std::cout << "Failed to create enemy, unknown enemy type: " << enemyType << std::endl;
				return nullptr;
			}
		}
	}
}