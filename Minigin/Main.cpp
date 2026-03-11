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
#include "ThrashCacheComponent.h"
#include "Commands/MoveCommand.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>

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
	pGamepadText->AddComponent<dae::TextComponent>("Use the D-Pad to move Bomberman", inputFont);
	pGamepadText->AddComponent<dae::RenderComponent>();
	pGamepadText->SetLocalPosition(10, 120);
	scene.Add(std::move(pGamepadText));

	auto pKeyboardText = std::make_unique<dae::GameObject>();
	pKeyboardText->AddComponent<dae::TextComponent>("Use WASD to move Balloom", inputFont);
	pKeyboardText->AddComponent<dae::RenderComponent>();
	pKeyboardText->SetLocalPosition(10, 140);
	scene.Add(std::move(pKeyboardText));

	auto pBomberman = std::make_unique<dae::GameObject>();
	pBomberman->AddComponent<dae::RenderComponent>("Bomberman.png");
	pBomberman->SetLocalPosition({ 300, 400, 0 });

	input.BindCommand(0, XINPUT_GAMEPAD_DPAD_UP, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBomberman.get(), 1.f, glm::vec2(0, -1)));
	input.BindCommand(0, XINPUT_GAMEPAD_DPAD_LEFT, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBomberman.get(), 1.f, glm::vec2(-1, 0)));
	input.BindCommand(0, XINPUT_GAMEPAD_DPAD_DOWN, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBomberman.get(), 1.f, glm::vec2(0, 1)));
	input.BindCommand(0, XINPUT_GAMEPAD_DPAD_RIGHT, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBomberman.get(), 1.f, glm::vec2(1, 0)));

	scene.Add(std::move(pBomberman));

	auto pBalloom = std::make_unique<dae::GameObject>();
	pBalloom->AddComponent<dae::RenderComponent>("Balloom.png");
	pBalloom->SetLocalPosition({ 300, 400, 0 });

	input.BindCommand(SDL_SCANCODE_W, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBalloom.get(), 1.f, glm::vec2(0, -1)));
	input.BindCommand(SDL_SCANCODE_A, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBalloom.get(), 1.f, glm::vec2(-1, 0)));
	input.BindCommand(SDL_SCANCODE_S, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBalloom.get(), 1.f, glm::vec2(0, 1)));
	input.BindCommand(SDL_SCANCODE_D, dae::KeyState::Down, std::make_unique<dae::MoveCommand>(pBalloom.get(), 1.f, glm::vec2(1, 0)));

	scene.Add(std::move(pBalloom));
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
