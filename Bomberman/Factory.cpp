#include "Factory.h"
#include <iostream>
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Components/AnimatedSpriteComponent.h"
#include "Components/CharacterControllerComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Components/AnimationControllerComponent.h"
#include "Components/EnemyBehaviourComponent.h"
#include "Components/ExplosionComponent.h"
#include "Components/TimerComponent.h"
#include "Components/HealthComponent.h"
#include "Utils.h"

std::unique_ptr<dae::GameObject> dae::EnemyFactory::CreateBalloom()
{
	auto pBalloom = std::make_unique<dae::GameObject>("Balloom");
	pBalloom->AddComponent<dae::RenderComponent>();
	pBalloom->AddComponent<dae::CharacterControllerComponent>(100.0f);
	auto* pBalloomCollider = pBalloom->AddComponent<dae::BoxColliderComponent>(56.0f, 62.0f, glm::vec2{ 4.0f, 1.0f }, true, 20.0f, 2.0f);
	pBalloomCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Enemy));
	pBalloomCollider->SetMask(0b0011'1011);
	pBalloom->AddComponent<dae::HealthComponent>(1);
	pBalloom->AddComponent<dae::AnimatedSpriteComponent>("Characters/Balloom.png", 4, 4, 0.1f, 64.0f, false);
	pBalloom->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 1, 0, 0, 1 });
	pBalloom->AddComponent<dae::EnemyBehaviourComponent>();
	
	return pBalloom;
}

std::unique_ptr<dae::GameObject> dae::EnemyFactory::CreateEnemy(const std::string& enemyType)
{
	if (enemyType == "balloom")
		return CreateBalloom();
	else
	{
		std::cout << "Failed to create enemy, unknown enemy type: " << enemyType << std::endl;
		return nullptr;
	}
}

std::unique_ptr<dae::GameObject> dae::BombFactory::CreateBomb()
{
	return std::unique_ptr<dae::GameObject>();
}

std::unique_ptr<dae::GameObject> dae::BombFactory::CreateExplosion()
{
	auto pExplosion = std::make_unique<dae::GameObject>("Explosion");
	pExplosion->AddComponent<dae::RenderComponent>("Interactables/Explosion.png");
	auto* pExplosionCollider = pExplosion->AddComponent<dae::BoxColliderComponent>(60.0f, 60.0f, glm::vec2{ 2.0f, 2.0f }, true);
	pExplosionCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Explosion));
	pExplosionCollider->SetMask(0b0001'1111);
	auto pTimer = pExplosion->AddComponent<dae::TimerComponent>(2.0f);
	//pExplosion->AddComponent<dae::ExplosionComponent>();
	pTimer->Start();

	return pExplosion;
}
