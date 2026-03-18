#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"
#include "RotatorComponent.h"
#include "AnimatedSpriteComponent.h"
#include "ThrashCacheComponent.h"
#include "Commands/MoveCommand.h"
#include "CharacterControllerComponent.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "Commands/DamageCommand.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "Commands/ScoreCommand.h"
#include "SteamAchievementComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto& input = dae::InputManager::GetInstance();

	auto pBackground = std::make_unique<dae::GameObject>();
	pBackground->AddComponent<dae::RenderComponent>("background.png");
	scene.Add(std::move(pBackground));

	auto pLogo = std::make_unique<dae::GameObject>();
	pLogo->AddComponent<dae::RenderComponent>("logo.png");
	pLogo->SetLocalPosition(358, 180);
	scene.Add(std::move(pLogo));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pTitle = std::make_unique<dae::GameObject>();
	pTitle->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	pTitle->AddComponent<dae::RenderComponent>();
	pTitle->SetLocalPosition(292, 20);
	scene.Add(std::move(pTitle));

	auto pFPSCounter = std::make_unique<dae::GameObject>();
	pFPSCounter->AddComponent<dae::RenderComponent>();
	pFPSCounter->AddComponent<dae::TextComponent>("60.0 FPS", font);
	pFPSCounter->AddComponent<dae::FPSComponent>();
	pFPSCounter->SetLocalPosition(10, 10);
	scene.Add(std::move(pFPSCounter));

	auto inputFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	auto pGamepadText = std::make_unique<dae::GameObject>();
	pGamepadText->AddComponent<dae::TextComponent>("Use the D-Pad to move Player 1. Press A to increase score and X to inflict damage.", inputFont);
	pGamepadText->AddComponent<dae::RenderComponent>();
	pGamepadText->SetLocalPosition(10, 120);
	scene.Add(std::move(pGamepadText));

	auto pKeyboardText = std::make_unique<dae::GameObject>();
	pKeyboardText->AddComponent<dae::TextComponent>("Use WASD to move Player 2. Press Space to increase score and F to inflict damage.", inputFont);
	pKeyboardText->AddComponent<dae::RenderComponent>();
	pKeyboardText->SetLocalPosition(10, 140);
	scene.Add(std::move(pKeyboardText));

	const float SPEED{ 100.0f };

	auto pPlayer1 = std::make_unique<dae::GameObject>();
	pPlayer1->AddComponent<dae::RenderComponent>();
	pPlayer1->AddComponent<dae::AnimatedSpriteComponent>("BombermanWalk.png", 4, 0.1f, 16.0f);
	pPlayer1->AddComponent<dae::CharacterControllerComponent>(SPEED);
	pPlayer1->AddComponent<dae::HealthComponent>(3);
	pPlayer1->AddComponent<dae::ScoreComponent>();
	pPlayer1->SetLocalPosition(300, 380);

	input.BindCommand(0, dae::GamePadButton::DPadUp, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, -1)));
	input.BindCommand(0, dae::GamePadButton::DPadLeft, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(-1, 0)));
	input.BindCommand(0, dae::GamePadButton::DPadDown, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, 1)));
	input.BindCommand(0, dae::GamePadButton::DPadRight, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(1, 0)));

	input.BindCommand(0, dae::GamePadButton::ButtonX, dae::KeyState::Pressed, std::make_unique<dae::DamageCommand>(pPlayer1.get()));
	input.BindCommand(0, dae::GamePadButton::ButtonA, dae::KeyState::Pressed, std::make_unique<dae::ScoreCommand>(pPlayer1.get()));

	auto pPlayer1LivesDisplay = std::make_unique<dae::GameObject>();
	pPlayer1LivesDisplay->AddComponent<dae::RenderComponent>();
	pPlayer1LivesDisplay->AddComponent<dae::TextComponent>("Lives: 0", inputFont);
	pPlayer1LivesDisplay->AddComponent<dae::HealthDisplayComponent>(pPlayer1.get());
	pPlayer1LivesDisplay->SetLocalPosition(10, 180);

	auto pPlayer1ScoreDisplay = std::make_unique<dae::GameObject>();
	pPlayer1ScoreDisplay->AddComponent<dae::RenderComponent>();
	pPlayer1ScoreDisplay->AddComponent<dae::TextComponent>("Score: 0", inputFont);
	pPlayer1ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(pPlayer1.get());
	pPlayer1ScoreDisplay->SetLocalPosition(10, 200);

	auto pPlayer2 = std::make_unique<dae::GameObject>();
	pPlayer2->AddComponent<dae::RenderComponent>();
	pPlayer2->AddComponent<dae::AnimatedSpriteComponent>("BombermanWalk.png", 4, 0.1f, 16.0f);
	pPlayer2->AddComponent<dae::CharacterControllerComponent>(SPEED / 2.0f);
	pPlayer2->AddComponent<dae::HealthComponent>(3);
	pPlayer2->AddComponent<dae::ScoreComponent>();
	pPlayer2->SetLocalPosition(340, 420);

	input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer2.get(), glm::vec2(0, -1)));
	input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer2.get(), glm::vec2(-1, 0)));
	input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer2.get(), glm::vec2(0, 1)));
	input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer2.get(), glm::vec2(1, 0)));

	input.BindCommand(SDL_SCANCODE_F, dae::KeyState::Pressed, std::make_unique<dae::DamageCommand>(pPlayer2.get()));
	input.BindCommand(SDL_SCANCODE_SPACE, dae::KeyState::Pressed, std::make_unique<dae::ScoreCommand>(pPlayer2.get()));

	auto pPlayer2LivesDisplay = std::make_unique<dae::GameObject>();
	pPlayer2LivesDisplay->AddComponent<dae::RenderComponent>();
	pPlayer2LivesDisplay->AddComponent<dae::TextComponent>("Lives: 0", inputFont);
	pPlayer2LivesDisplay->AddComponent<dae::HealthDisplayComponent>(pPlayer2.get());
	pPlayer2LivesDisplay->SetLocalPosition(920, 180);

	auto pPlayer2ScoreDisplay = std::make_unique<dae::GameObject>();
	pPlayer2ScoreDisplay->AddComponent<dae::RenderComponent>();
	pPlayer2ScoreDisplay->AddComponent<dae::TextComponent>("Score: 0", inputFont);
	pPlayer2ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(pPlayer2.get());
	pPlayer2ScoreDisplay->SetLocalPosition(920, 200);

#if USE_STEAMWORKS
	auto pSteamAchievement = std::make_unique<dae::GameObject>();
	pSteamAchievement->AddComponent<dae::SteamAchievementComponent>(pPlayer1.get());
	pSteamAchievement->AddComponent<dae::SteamAchievementComponent>(pPlayer2.get());
	scene.Add(std::move(pSteamAchievement));
#endif

	scene.Add(std::move(pPlayer1));
	scene.Add(std::move(pPlayer1LivesDisplay));
	scene.Add(std::move(pPlayer1ScoreDisplay));

	scene.Add(std::move(pPlayer2));
	scene.Add(std::move(pPlayer2LivesDisplay));
	scene.Add(std::move(pPlayer2ScoreDisplay));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
