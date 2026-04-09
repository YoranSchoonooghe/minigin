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
#include "AnimatedSpriteComponent.h"
#include "Commands/MoveCommand.h"
#include "CharacterControllerComponent.h"
#include "HealthComponent.h"
#include "HealthDisplayComponent.h"
#include "Commands/DamageCommand.h"
#include "ScoreComponent.h"
#include "ScoreDisplayComponent.h"
#include "Commands/ScoreCommand.h"
#include "Renderer.h"
#include "Components/TimerComponent.h"
#include "Components/TimerDisplayComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Commands/DropBombCommand.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto& input = dae::InputManager::GetInstance();

	SDL_SetRenderDrawBlendMode(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_BLENDMODE_BLEND);
	dae::Renderer::GetInstance().SetBackgroundColor({ 161, 161, 161, 255 });

	auto pBackground = std::make_unique<dae::GameObject>();
	pBackground->AddComponent<dae::RenderComponent>("LevelBackground.png");
	pBackground->SetLocalPosition(0.0f, 224.0f);
	scene.Add(std::move(pBackground));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pFPSCounter = std::make_unique<dae::GameObject>();
	pFPSCounter->AddComponent<dae::RenderComponent>();
	pFPSCounter->AddComponent<dae::TextComponent>("60.0 FPS", font);
	pFPSCounter->AddComponent<dae::FPSComponent>();
	pFPSCounter->SetLocalPosition(10, 10);
	scene.Add(std::move(pFPSCounter));

	auto inputFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto pGamepadText = std::make_unique<dae::GameObject>();
	pGamepadText->AddComponent<dae::TextComponent>("Use the D-Pad to move Player 1. Press A to increase score and X to inflict damage.", inputFont);
	pGamepadText->AddComponent<dae::RenderComponent>();
	pGamepadText->SetLocalPosition(10, 80);
	scene.Add(std::move(pGamepadText));

	auto pKeyboardText = std::make_unique<dae::GameObject>();
	pKeyboardText->AddComponent<dae::TextComponent>("Use WASD to move Player 2. Press Space to increase score and F to inflict damage.", inputFont);
	pKeyboardText->AddComponent<dae::RenderComponent>();
	pKeyboardText->SetLocalPosition(10, 110);
	scene.Add(std::move(pKeyboardText));

	const float SPEED{ 200.0f };

	auto pPlayer1 = std::make_unique<dae::GameObject>();
	pPlayer1->AddComponent<dae::RenderComponent>();
	pPlayer1->AddComponent<dae::AnimatedSpriteComponent>("Bomberman.png", 4, 0.1f, 64.0f);
	pPlayer1->AddComponent<dae::CharacterControllerComponent>(SPEED);
	pPlayer1->AddComponent<dae::HealthComponent>(3);
	pPlayer1->AddComponent<dae::ScoreComponent>();
	pPlayer1->AddComponent<dae::BoxColliderComponent>(32.0f, 64.0f, glm::vec2{ 16.0f, 0.0f });
	pPlayer1->SetLocalPosition(64, 288);

	input.BindCommand(0, dae::GamePadButton::DPadUp, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, -1)));
	input.BindCommand(0, dae::GamePadButton::DPadLeft, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(-1, 0)));
	input.BindCommand(0, dae::GamePadButton::DPadDown, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, 1)));
	input.BindCommand(0, dae::GamePadButton::DPadRight, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(1, 0)));

	input.BindCommand(0, dae::GamePadButton::ButtonX, dae::KeyState::Pressed, std::make_unique<dae::DamageCommand>(pPlayer1.get()));
	input.BindCommand(0, dae::GamePadButton::ButtonA, dae::KeyState::Pressed, std::make_unique<dae::ScoreCommand>(pPlayer1.get()));
	input.BindCommand(0, dae::GamePadButton::ButtonY, dae::KeyState::Pressed, std::make_unique<dae::DropBombCommand>(pPlayer1.get()));

	input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, -1)));
	input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(-1, 0)));
	input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(0, 1)));
	input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pPlayer1.get(), glm::vec2(1, 0)));

	input.BindCommand(SDL_SCANCODE_F, dae::KeyState::Pressed, std::make_unique<dae::DamageCommand>(pPlayer1.get()));
	input.BindCommand(SDL_SCANCODE_SPACE, dae::KeyState::Pressed, std::make_unique<dae::ScoreCommand>(pPlayer1.get()));

	auto pPlayer1LivesDisplay = std::make_unique<dae::GameObject>();
	pPlayer1LivesDisplay->AddComponent<dae::RenderComponent>();
	pPlayer1LivesDisplay->AddComponent<dae::TextComponent>("LEFT 0", inputFont);
	pPlayer1LivesDisplay->AddComponent<dae::HealthDisplayComponent>(pPlayer1.get(), "LEFT ");
	pPlayer1LivesDisplay->SetLocalPosition(900, 180);

	auto pPlayer1ScoreDisplay = std::make_unique<dae::GameObject>();
	pPlayer1ScoreDisplay->AddComponent<dae::RenderComponent>();
	pPlayer1ScoreDisplay->AddComponent<dae::TextComponent>("00", inputFont);
	pPlayer1ScoreDisplay->AddComponent<dae::ScoreDisplayComponent>(pPlayer1.get(), "");
	pPlayer1ScoreDisplay->SetLocalPosition(500, 180);

	scene.Add(std::move(pPlayer1));
	scene.Add(std::move(pPlayer1LivesDisplay));
	scene.Add(std::move(pPlayer1ScoreDisplay));

	//auto pBomb = std::make_unique<dae::GameObject>();
	//pBomb->AddComponent<dae::RenderComponent>();
	//pBomb->AddComponent<dae::AnimatedSpriteComponent>("Bomb.png", 4, 0.2f, 64.0f);
	//auto pTimer = pBomb->AddComponent<dae::TimerComponent>(3.0f);
	//pTimer->Start();
	//pBomb->SetLocalPosition(64, 416);
	//scene.Add(std::move(pBomb));

	auto pLevelTimer = std::make_unique<dae::GameObject>();
	auto pLevelTimerComponent = pLevelTimer->AddComponent<dae::TimerComponent>(201.0f);
	pLevelTimerComponent->Start();
	auto pLevelTimerDisplay = std::make_unique<dae::GameObject>();
	pLevelTimerDisplay->AddComponent<dae::RenderComponent>();
	pLevelTimerDisplay->AddComponent<dae::TextComponent>("TIME 200", inputFont);
	pLevelTimerDisplay->AddComponent<dae::TimerDisplayComponent>(pLevelTimer.get(), "TIME ");
	pLevelTimerDisplay->SetLocalPosition(20, 180);
	scene.Add(std::move(pLevelTimer));
	scene.Add(std::move(pLevelTimerDisplay));
}

int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}
