#include "PlayState.h"
#include <SDL3/SDL.h>
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Components/TextComponent.h"
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
#include "Components/ExitComponent.h"
#include "Components/RespawnComponent.h"
#include "Components/BrickComponent.h"
#include "Components/ItemDropperComponent.h"
#include "Audio/ServiceLocator.h"
#include "GameManager.h"
#include "Utils.h"
#include <random>
#include <algorithm>
#include "StageLoader.h"
#include "Factory.h"
#include "Events/EventManager.h"
#include "Events/Event.h"
#include "Commands/SkipStageCommand.h"

void dae::PlayState::Enter()
{
	LoadScene();

	EventManager::GetInstance().AddObserver(this);
}

void dae::PlayState::Exit()
{
	ServiceLocator::GetSoundSystem().StopAll();
	UnbindCommands();

	EventManager::GetInstance().RemoveObserver(this);
}

void dae::PlayState::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnEnemyDied"):
	{
		--m_enemiesCount;
		if (m_enemiesCount == 0)
		{
			m_pExit->OpenSesame();
		}
	}
		break;
	}
}

void dae::PlayState::LoadScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto& input = dae::InputManager::GetInstance();

	auto stageData = StageLoader::LoadStage(ResourceManager::GetInstance().GetDataPath()/"StageData/stage03.json");

	for (const auto& [type, count] : stageData.enemies)
	{
		m_enemiesCount += count;
	}

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
	auto* pPlayerCollider = pPlayer1->AddComponent<dae::BoxColliderComponent>(48.0f, 62.0f, glm::vec2{ 8.0f, 1.0f }, true, 20.0f, 2.0f);
	constexpr uint8_t playerLayer = static_cast<uint8_t>(CollisionUtils::Layer::Player);
	pPlayerCollider->SetLayer(playerLayer);
	pPlayerCollider->SetMask(static_cast<uint8_t>(~playerLayer));
	pPlayer1->AddComponent<dae::AnimatedSpriteComponent>("Characters/Bomberman.png", 4, 4, 0.07f, 64.0f, false);
	pPlayer1->AddComponent<dae::AnimationControllerComponent>(dae::SpritesheetMoveDirection{ 2, 3, 1, 0 });
	auto* pPlayerHealth = pPlayer1->AddComponent<dae::HealthComponent>(1);
	pPlayer1->AddComponent<dae::ScoreComponent>(GameManager::GetInstance().GetScore());
	pPlayer1->AddComponent<dae::BombermanComponent>();
	auto playerPos{ GridUtils::GetPositionFromCell(GameManager::GetInstance().GetGrid(), 1, 1) };
	pPlayer1->SetLocalPosition(playerPos.x, playerPos.y);

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

	auto pRestartTimer = std::make_unique<dae::GameObject>("RestartTimer");
	pRestartTimer->AddComponent<dae::TimerComponent>(3.0f);
	pRestartTimer->AddComponent<RespawnComponent>(pPlayerHealth);
	scene.Add(std::move(pRestartTimer));

	auto pUI = std::make_unique<dae::GameObject>("UI");

	//auto pPlayer1LivesDisplay = std::make_unique<dae::GameObject>("Player1HP");
	//pPlayer1LivesDisplay->AddComponent<dae::RenderComponent>("", true);
	//pPlayer1LivesDisplay->AddComponent<dae::TextComponent>("LEFT 0", inputFont);
	//pPlayer1LivesDisplay->AddComponent<dae::HealthDisplayComponent>(pPlayer1.get(), "LEFT ");
	//pPlayer1LivesDisplay->SetLocalPosition(900, 180);
	//pPlayer1LivesDisplay->SetParent(pUI.get());

	auto pPlayer1LivesDisplay = std::make_unique<dae::GameObject>("Player1HP");
	pPlayer1LivesDisplay->AddComponent<dae::RenderComponent>("", true);
	pPlayer1LivesDisplay->AddComponent<dae::TextComponent>("LEFT " + std::to_string(GameManager::GetInstance().GetLives()), inputFont);
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

	const float tileSize{ GameManager::GetInstance().GetGrid().cellSize };
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

	auto validGridCells = LevelUtils::GetValidBrickCells(GameManager::GetInstance().GetGrid());

	std::random_device rd;
	std::mt19937 g(rd());

	std::ranges::shuffle(validGridCells, g);

	auto pBricks = std::make_unique<dae::GameObject>("Bricks");
	for (int index{ 0 }; index < stageData.bricks; ++index)
	{
		auto position = GridUtils::GetPositionFromCell(
			GameManager::GetInstance().GetGrid(), 
			validGridCells[index].row, 
			validGridCells[index].col
		);

		auto pBrick = ItemFactory::CreateBrick();
		pBrick->SetLocalPosition(position.x, position.y);
		pBrick->SetParent(pBricks.get());

		if (index == 0)
		{
			auto pExit = ItemFactory::CreateExit();
			m_pExit = pExit.get()->GetComponent<ExitComponent>();
			pExit->SetLocalPosition(position.x, position.y);
			pExit->SetActive(false);

			pBrick->AddComponent<ItemDropperComponent>(pExit.get());

			scene.Add(std::move(pExit));
		}
		else if (index == 1)
		{
			auto pPowerUp = ItemFactory::CreatePowerUp(1);
			pPowerUp->SetLocalPosition(position.x, position.y);
			pPowerUp->SetActive(false);

			pBrick->AddComponent<ItemDropperComponent>(pPowerUp.get());

			scene.Add(std::move(pPowerUp));
		}

		pBrick->AddComponent<BrickComponent>();
		scene.Add(std::move(pBrick));
	}
	scene.Add(std::move(pBricks));

	auto pEnemies = std::make_unique<dae::GameObject>("Enemies");
	int startIndex{ stageData.bricks };
	for (const auto& [type, count] : stageData.enemies)
	{
		for (int index{ startIndex }; index < (startIndex + count); ++index)
		{
			auto position = GridUtils::GetPositionFromCell(
				GameManager::GetInstance().GetGrid(),
				validGridCells[index].row,
				validGridCells[index].col
			);

			auto pEnemy{ EnemyFactory::CreateEnemy(type) };
			pEnemy->SetLocalPosition(position.x, position.y);
			pEnemy->SetParent(pEnemies.get());

			scene.Add(std::move(pEnemy));
		}

		startIndex += count;
	}
	scene.Add(std::move(pEnemies));

	input.BindCommand(SDL_SCANCODE_F1, KeyState::Pressed, std::make_unique<SkipStageCommand>());

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

	input.UnbindCommand(SDL_SCANCODE_SPACE, dae::KeyState::Pressed);

	input.UnbindCommand(SDL_SCANCODE_F1, dae::KeyState::Pressed);
}
