#include "PlayState.h"
#include <SDL3/SDL.h>
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RenderComponent.h"
#include "Components/AnimatedSpriteComponent.h"
#include "Commands/MoveCommand.h"
#include "Components/CharacterControllerComponent.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Renderer.h"
#include "Components/TimerComponent.h"
#include "Components/TimerDisplayComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Commands/DropBombCommand.h"
#include "Components/AnimationControllerComponent.h"
#include "Components/CameraComponent.h"
#include "Components/PowerUpComponent.h"
#include "Components/BombermanComponent.h"
#include "Components/EnemyBehaviourComponent.h"
#include "Audio/ServiceLocator.h"

void dae::PlayState::Enter()
{
	LoadScene();
}

void dae::PlayState::Exit()
{
	UnbindCommands();
}

void dae::PlayState::LoadScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto& input = dae::InputManager::GetInstance();

	dae::Renderer::GetInstance().SetBackgroundColor({ 161, 161, 161, 255 });

	auto pBackground = std::make_unique<dae::GameObject>("LevelBackground");
	pBackground->AddComponent<dae::RenderComponent>("LevelBackground.png");
	pBackground->SetLocalPosition(0.0f, 224.0f);
	scene.Add(std::move(pBackground));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pFPSCounter = std::make_unique<dae::GameObject>("FPSCounter");
	pFPSCounter->AddComponent<dae::RenderComponent>("", true);
	pFPSCounter->AddComponent<dae::TextComponent>("60.0 FPS", font);
	pFPSCounter->AddComponent<dae::FPSComponent>();
	pFPSCounter->SetLocalPosition(10, 10);
	scene.Add(std::move(pFPSCounter));

	auto inputFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto pGamepadText = std::make_unique<dae::GameObject>("Player1Text");
	pGamepadText->AddComponent<dae::TextComponent>("Use the D-Pad/WASD to move. Press A/SPACE to drop a bomb.", inputFont);
	pGamepadText->AddComponent<dae::RenderComponent>("", true);
	pGamepadText->SetLocalPosition(10, 80);
	scene.Add(std::move(pGamepadText));

	const float SPEED{ 200.0f };

	auto pPlayer1 = std::make_unique<dae::GameObject>("Bomberman");
	pPlayer1->AddComponent<dae::RenderComponent>();
	pPlayer1->AddComponent<dae::CharacterControllerComponent>(SPEED);
	pPlayer1->AddComponent<dae::BoxColliderComponent>(48.0f, 62.0f, glm::vec2{ 8.0f, 1.0f }, true, 20.0f, 2.0f);
	pPlayer1->AddComponent<dae::AnimatedSpriteComponent>("Characters/Bomberman.png", 4, 4, 0.07f, 64.0f, false);
	pPlayer1->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 2, 3, 1, 0 });
	pPlayer1->AddComponent<dae::HealthComponent>(3);
	pPlayer1->AddComponent<dae::ScoreComponent>();
	pPlayer1->AddComponent<dae::BombermanComponent>();
	pPlayer1->SetLocalPosition(64, 288);

	input.BindCommand(0, dae::GamePadButton::DPadUp, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, -1)));
	input.BindCommand(0, dae::GamePadButton::DPadLeft, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(-1, 0)));
	input.BindCommand(0, dae::GamePadButton::DPadDown, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, 1)));
	input.BindCommand(0, dae::GamePadButton::DPadRight, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(1, 0)));

	input.BindCommand(0, dae::GamePadButton::ButtonA, dae::KeyState::Pressed, std::make_unique<dae::DropBombCommand>(pPlayer1.get()));

	input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, -1)));
	input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(-1, 0)));
	input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, 1)));
	input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(1, 0)));

	input.BindCommand(SDL_SCANCODE_SPACE, dae::KeyState::Pressed, std::make_unique<dae::DropBombCommand>(pPlayer1.get()));

	auto pUI = std::make_unique<dae::GameObject>("UI");

	auto pPlayer1LivesDisplay = std::make_unique<dae::GameObject>("Player1HP");
	pPlayer1LivesDisplay->AddComponent<dae::RenderComponent>("", true);
	pPlayer1LivesDisplay->AddComponent<dae::TextComponent>("LEFT 0", inputFont);
	pPlayer1LivesDisplay->AddComponent<dae::HealthDisplayComponent>(pPlayer1.get(), "LEFT ");
	pPlayer1LivesDisplay->SetLocalPosition(900, 180);
	pPlayer1LivesDisplay->SetParent(pUI.get());

	auto pPlayer1ScoreDisplay = std::make_unique<dae::GameObject>("Player1Score");
	pPlayer1ScoreDisplay->AddComponent<dae::RenderComponent>("", true);
	pPlayer1ScoreDisplay->AddComponent<dae::TextComponent>("00", inputFont);
	pPlayer1ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(pPlayer1.get(), "");
	pPlayer1ScoreDisplay->SetLocalPosition(500, 180);
	pPlayer1ScoreDisplay->SetParent(pUI.get());

	auto pCamera = std::make_unique<dae::GameObject>("Camera");
	pCamera->AddComponent<dae::CameraComponent>(pPlayer1.get(), SDL_FRect(0.0f, 0.0f, 1984.0f, 1024.0f), glm::vec2(32.0f, 32.0f));
	scene.SetCamera(pCamera.get());
	scene.Add(std::move(pCamera));

	scene.Add(std::move(pPlayer1));
	scene.Add(std::move(pPlayer1LivesDisplay));
	scene.Add(std::move(pPlayer1ScoreDisplay));

	auto pLevelTimer = std::make_unique<dae::GameObject>("LevelTimer");
	auto pLevelTimerComponent = pLevelTimer->AddComponent<dae::TimerComponent>(201.0f);
	auto pLevelTimerDisplay = std::make_unique<dae::GameObject>("LevelTimerDisplay");
	pLevelTimerDisplay->AddComponent<dae::RenderComponent>("", true);
	pLevelTimerDisplay->AddComponent<dae::TextComponent>("TIME 200", inputFont);
	pLevelTimerDisplay->AddComponent<dae::TimerDisplayComponent>(pLevelTimer.get(), "TIME ");
	pLevelTimerDisplay->SetLocalPosition(20, 180);
	pLevelTimerDisplay->SetParent(pUI.get());
	scene.Add(std::move(pLevelTimerDisplay));
	pLevelTimerComponent->Start();
	scene.Add(std::move(pLevelTimer));

	scene.Add(std::move(pUI));

	auto pPillars = std::make_unique<dae::GameObject>("Pillars");

	const float tileSize{ 64.0f };
	for (int i = 0; i < 14; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			auto pPillar = std::make_unique<dae::GameObject>("Pillar");
			pPillar->AddComponent<dae::BoxColliderComponent>(tileSize, tileSize);
			pPillar->SetLocalPosition(128.0f + 2 * tileSize * i, 352.0f + 2 * tileSize * j);
			pPillar->SetParent(pPillars.get());
			scene.Add(std::move(pPillar));
		}
	}

	scene.Add(std::move(pPillars));

	auto pLevelBorder = std::make_unique<dae::GameObject>("LevelBorder");

	auto pTopBorder = std::make_unique<dae::GameObject>("TopBorder");
	pTopBorder->AddComponent<dae::BoxColliderComponent>(1984.0f, tileSize);
	pTopBorder->SetLocalPosition(0.0f, 224.0f);
	pTopBorder->SetParent(pLevelBorder.get());
	scene.Add(std::move(pTopBorder));

	auto pBottomBorder = std::make_unique<dae::GameObject>("BottomBorder");
	pBottomBorder->AddComponent<dae::BoxColliderComponent>(1984.0f, tileSize);
	pBottomBorder->SetLocalPosition(0.0f, 992.0f);
	pBottomBorder->SetParent(pLevelBorder.get());
	scene.Add(std::move(pBottomBorder));

	auto pLeftBorder = std::make_unique<dae::GameObject>("LeftBorder");
	pLeftBorder->AddComponent<dae::BoxColliderComponent>(tileSize, 704.0f);
	pLeftBorder->SetLocalPosition(0.0f, 288.0f);
	pLeftBorder->SetParent(pLevelBorder.get());
	scene.Add(std::move(pLeftBorder));

	auto pRightBorder = std::make_unique<dae::GameObject>("RightBorder");
	pRightBorder->AddComponent<dae::BoxColliderComponent>(tileSize, 704.0f);
	pRightBorder->SetLocalPosition(1920.0f, 288.0f);
	pRightBorder->SetParent(pLevelBorder.get());
	scene.Add(std::move(pRightBorder));

	scene.Add(std::move(pLevelBorder));

	auto pExit = std::make_unique<dae::GameObject>("Exit");
	pExit->AddComponent<dae::RenderComponent>("Interactables/Exit.png");
	pExit->AddComponent<dae::BoxColliderComponent>(tileSize, tileSize, glm::vec2{ 0.0f, 0.0f }, true);
	pExit->SetLocalPosition(384.0f, 288.0f);
	scene.Add(std::move(pExit));

	auto pBrick = std::make_unique<dae::GameObject>("Brick");
	pBrick->AddComponent<dae::RenderComponent>("Interactables/Brick.png");
	pBrick->AddComponent<dae::BoxColliderComponent>(tileSize, tileSize);
	pBrick->SetLocalPosition(256.0f, 288.0f);
	scene.Add(std::move(pBrick));

	auto pPowerUp = std::make_unique<dae::GameObject>("PowerUp");
	pPowerUp->AddComponent<dae::RenderComponent>("Interactables/PowerUps.png");
	pPowerUp->AddComponent<dae::BoxColliderComponent>(40.0f, 40.0f, glm::vec2{ 12.0f, 12.0f }, true);
	pPowerUp->AddComponent<dae::PowerUpComponent>(dae::PowerUpComponent::Type::ExtraBomb);
	pPowerUp->SetLocalPosition(256.0f, 416.0f);
	scene.Add(std::move(pPowerUp));

	auto pBalloom = std::make_unique<dae::GameObject>("Balloom");
	pBalloom->AddComponent<dae::RenderComponent>();
	pBalloom->AddComponent<dae::CharacterControllerComponent>(SPEED / 2.0f);
	pBalloom->AddComponent<dae::BoxColliderComponent>(48.0f, 62.0f, glm::vec2{ 8.0f, 1.0f }, true, 20.0f, 2.0f);
	pBalloom->AddComponent<dae::AnimatedSpriteComponent>("Characters/Balloom.png", 4, 4, 0.1f, 64.0f, false);
	pBalloom->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 1, 0, 1, 0 });
	pBalloom->AddComponent<dae::EnemyBehaviourComponent>();
	pBalloom->SetLocalPosition(448.0f, 608.0f);

	scene.Add(std::move(pBalloom));

	dae::ServiceLocator::GetSoundSystem().AddAudioSource(dae::AudioSource(1, "Audio/GameOver.wav"));
	dae::ServiceLocator::GetSoundSystem().AddAudioSource(dae::AudioSource(2, "Audio/DropBomb.wav"));
	dae::ServiceLocator::GetSoundSystem().AddAudioSource(dae::AudioSource(3, "Audio/BombExplode.wav"));
	dae::ServiceLocator::GetSoundSystem().AddAudioSource(dae::AudioSource(4, "Audio/PowerUp.wav"));
	dae::ServiceLocator::GetSoundSystem().AddAudioSource(dae::AudioSource(5, "Audio/MainMusic.mp3"));

	dae::ServiceLocator::GetSoundSystem().Play(5, 1.0f, true);
}

void dae::PlayState::UnbindCommands()
{
	auto& input = dae::InputManager::GetInstance();

	input.UnbindCommand(0, dae::GamePadButton::DPadUp, dae::KeyState::Down);
	input.UnbindCommand(0, dae::GamePadButton::DPadLeft, dae::KeyState::Down);
	input.UnbindCommand(0, dae::GamePadButton::DPadDown, dae::KeyState::Down);
	input.UnbindCommand(0, dae::GamePadButton::DPadRight, dae::KeyState::Down);

	input.UnbindCommand(0, dae::GamePadButton::ButtonA, dae::KeyState::Pressed);

	input.UnbindCommand(SDL_SCANCODE_W, dae::KeyState::Down);
	input.UnbindCommand(SDL_SCANCODE_A, dae::KeyState::Down);
	input.UnbindCommand(SDL_SCANCODE_S, dae::KeyState::Down);
	input.UnbindCommand(SDL_SCANCODE_D, dae::KeyState::Down);
}
