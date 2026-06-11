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
	pBalloom->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 1, 0, 0, 1 }, 2);
	pBalloom->AddComponent<TimerComponent>(2.0f);
	pBalloom->AddComponent<dae::EnemyBehaviourComponent>();
	
	return pBalloom;
}

std::unique_ptr<dae::GameObject> dae::EnemyFactory::CreateOneal()
{
	auto pOneal = std::make_unique<dae::GameObject>("Oneal");
	pOneal->AddComponent<dae::RenderComponent>();
	pOneal->AddComponent<dae::CharacterControllerComponent>(160.0f);
	auto* pBalloomCollider = pOneal->AddComponent<dae::BoxColliderComponent>(56.0f, 62.0f, glm::vec2{ 4.0f, 1.0f }, true, 20.0f, 2.0f);
	pBalloomCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Enemy));
	pBalloomCollider->SetMask(0b0011'1011);
	pOneal->AddComponent<dae::HealthComponent>(1);
	pOneal->AddComponent<dae::AnimatedSpriteComponent>("Characters/Oneal.png", 4, 4, 0.1f, 64.0f, false);
	pOneal->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 1, 0, 0, 1 }, 2);
	pOneal->AddComponent<TimerComponent>(2.0f);
	pOneal->AddComponent<dae::EnemyBehaviourComponent>();

	return pOneal;
}

std::unique_ptr<dae::GameObject> dae::EnemyFactory::CreateDoll()
{
	auto pDoll = std::make_unique<dae::GameObject>("Doll");
	pDoll->AddComponent<dae::RenderComponent>();
	pDoll->AddComponent<dae::CharacterControllerComponent>(160.0f);
	auto* pBalloomCollider = pDoll->AddComponent<dae::BoxColliderComponent>(56.0f, 62.0f, glm::vec2{ 4.0f, 1.0f }, true, 20.0f, 2.0f);
	pBalloomCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Enemy));
	pBalloomCollider->SetMask(0b0011'1011);
	pDoll->AddComponent<dae::HealthComponent>(1);
	pDoll->AddComponent<dae::AnimatedSpriteComponent>("Characters/Doll.png", 4, 4, 0.1f, 64.0f, false);
	pDoll->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 1, 0, 0, 1 }, 2);
	pDoll->AddComponent<TimerComponent>(2.0f);
	pDoll->AddComponent<dae::EnemyBehaviourComponent>();

	return pDoll;
}

std::unique_ptr<dae::GameObject> dae::EnemyFactory::CreateMinvo()
{
	auto pMinvo = std::make_unique<dae::GameObject>("Minvo");
	pMinvo->AddComponent<dae::RenderComponent>();
	pMinvo->AddComponent<dae::CharacterControllerComponent>(200.0f);
	auto* pBalloomCollider = pMinvo->AddComponent<dae::BoxColliderComponent>(56.0f, 62.0f, glm::vec2{ 4.0f, 1.0f }, true, 20.0f, 2.0f);
	pBalloomCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Enemy));
	pBalloomCollider->SetMask(0b0011'1011);
	pMinvo->AddComponent<dae::HealthComponent>(1);
	pMinvo->AddComponent<dae::AnimatedSpriteComponent>("Characters/Minvo.png", 4, 4, 0.1f, 64.0f, false);
	pMinvo->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 1, 0, 0, 1 }, 2);
	pMinvo->AddComponent<TimerComponent>(2.0f);
	pMinvo->AddComponent<dae::EnemyBehaviourComponent>();

	return pMinvo;
}

std::unique_ptr<dae::GameObject> dae::EnemyFactory::CreateEnemy(const std::string& enemyType)
{
	if (enemyType == "balloom")
		return CreateBalloom();
	else if (enemyType == "oneal")
		return CreateOneal();
	else if (enemyType == "doll")
		return CreateDoll();
	else if (enemyType == "minvo")
		return CreateMinvo();
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
