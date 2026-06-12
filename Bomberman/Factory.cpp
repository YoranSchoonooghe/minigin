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
#include "Components/ExitComponent.h"
#include "Components/PowerUpComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/BombermanComponent.h"
#include "Components/BombComponent.h"
#include "Utils.h"
#include "GameManager.h"

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
	auto pBomb = std::make_unique<GameObject>("Bomb");
	pBomb->AddComponent<RenderComponent>();
	pBomb->AddComponent<AnimatedSpriteComponent>("Interactables/Bomb.png", 1, 4, 0.2f, 64.0f);
	auto* pBombCollider = pBomb->AddComponent<BoxColliderComponent>(64.0f, 64.0f, glm::vec2{ 0.0f, 0.0f }, true);
	pBombCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Bomb));
	pBomb->AddComponent<TimerComponent>(3.0f);
	pBomb->AddComponent<BombComponent>();

	return pBomb;
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

std::unique_ptr<dae::GameObject> dae::ItemFactory::CreateExit()
{
	auto pExit = std::make_unique<dae::GameObject>("Exit");
	pExit->AddComponent<dae::RenderComponent>("Interactables/Exit.png");
	auto* pExitCollider = pExit->AddComponent<dae::BoxColliderComponent>(32.0f, 32.0f, glm::vec2{ 16.0f, 16.0f }, true);
	pExitCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Exit));
	pExitCollider->SetMask(static_cast<uint8_t>(CollisionUtils::Layer::Player));
	pExit->AddComponent<dae::ExitComponent>();

	return pExit;
}

std::unique_ptr<dae::GameObject> dae::ItemFactory::CreatePowerUp(const std::string& powerUpType)
{
	PowerUpComponent::Type powerupType{};

	if (powerUpType == "flames")
		powerupType = PowerUpComponent::Type::Flames;
	else if (powerUpType == "bomb")
		powerupType = PowerUpComponent::Type::ExtraBomb;
	else if (powerUpType == "detonator")
		powerupType = PowerUpComponent::Type::Detonator;

	auto pPowerUp = std::make_unique<GameObject>("PowerUp");
	pPowerUp->AddComponent<RenderComponent>("Interactables/PowerUps.png");
	auto* pPowerUpCollider = pPowerUp->AddComponent<BoxColliderComponent>(40.0f, 40.0f, glm::vec2{ 12.0f, 12.0f }, true);
	pPowerUpCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::PowerUp));
	pPowerUpCollider->SetMask(static_cast<uint8_t>(CollisionUtils::Layer::Player));
	pPowerUp->AddComponent<PowerUpComponent>(powerupType);

	return pPowerUp;
}

std::unique_ptr<dae::GameObject> dae::ItemFactory::CreateBrick()
{
	float const tileSize{ GameManager::GetInstance().GetGrid().cellSize };

	auto pBrick = std::make_unique<dae::GameObject>("Brick");
	pBrick->AddComponent<dae::RenderComponent>("Interactables/Brick.png");
	auto* pBrickCollider = pBrick->AddComponent<dae::BoxColliderComponent>(tileSize, tileSize);
	pBrickCollider->SetLayer(static_cast<uint8_t>(CollisionUtils::Layer::Brick));
	pBrickCollider->SetMask(0b0011'0110);

	return pBrick;
}

std::unique_ptr<dae::GameObject> dae::PlayerFactory::CreateBomberman()
{
	auto pBomberman = std::make_unique<GameObject>("Bomberman");
	pBomberman->AddComponent<RenderComponent>();
	pBomberman->AddComponent<CharacterControllerComponent>(200.0f);
	auto* pPlayerCollider = pBomberman->AddComponent<BoxColliderComponent>(48.0f, 62.0f, glm::vec2{ 8.0f, 1.0f }, true, 20.0f, 2.0f);
	constexpr uint8_t playerLayer = static_cast<uint8_t>(CollisionUtils::Layer::Player);
	pPlayerCollider->SetLayer(playerLayer);
	pPlayerCollider->SetMask(static_cast<uint8_t>(~playerLayer));
	pBomberman->AddComponent<AnimatedSpriteComponent>("Characters/Bomberman.png", 4, 4, 0.07f, 64.0f, false);
	pBomberman->AddComponent<AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 2, 3, 1, 0 });
	pBomberman->AddComponent<dae::HealthComponent>(1);
	pBomberman->AddComponent<ScoreComponent>(GameManager::GetInstance().GetScore());
	pBomberman->AddComponent<BombermanComponent>();

	return pBomberman;
}

std::unique_ptr<dae::GameObject> dae::PlayerFactory::CreateBomberwoman()
{
	auto pBomberwoman = std::make_unique<GameObject>("Bomberwoman");
	pBomberwoman->AddComponent<RenderComponent>();
	pBomberwoman->AddComponent<CharacterControllerComponent>(200.0f);
	auto* pPlayerCollider = pBomberwoman->AddComponent<BoxColliderComponent>(48.0f, 62.0f, glm::vec2{ 8.0f, 1.0f }, true, 20.0f, 2.0f);
	constexpr uint8_t playerLayer = static_cast<uint8_t>(CollisionUtils::Layer::Player);
	pPlayerCollider->SetLayer(playerLayer);
	pPlayerCollider->SetMask(static_cast<uint8_t>(~playerLayer));
	pBomberwoman->AddComponent<AnimatedSpriteComponent>("Characters/Bomberwoman.png", 4, 4, 0.07f, 64.0f, false);
	pBomberwoman->AddComponent<AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 2, 3, 1, 0 });
	pBomberwoman->AddComponent<dae::HealthComponent>(1);
	pBomberwoman->AddComponent<ScoreComponent>(GameManager::GetInstance().GetScore());
	pBomberwoman->AddComponent<BombermanComponent>();

	return pBomberwoman;
}
