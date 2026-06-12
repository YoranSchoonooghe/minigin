#include "GameModeSelectionState.h"
#include <SDL3/SDL.h>
#include "Renderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Components/TextComponent.h"
#include "Commands/StartGameModeCommand.h"
#include "Commands/SelectGameModeCommand.h"
#include <memory>

void dae::GameModeSelectionState::Enter()
{
	LoadScene();
}

void dae::GameModeSelectionState::Exit()
{
	UnbindCommands();
}

void dae::GameModeSelectionState::LoadScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene();
	auto& input = InputManager::GetInstance();

	dae::Renderer::GetInstance().SetBackgroundColor({ 0, 0, 0, 255 });

	auto pIndicator = std::make_unique<GameObject>("Indicator");
	pIndicator->AddComponent<RenderComponent>("Indicator.png", true);
	pIndicator->SetLocalPosition(220, 300);

	input.BindCommand(0, GamePadButton::DPadDown, KeyState::Pressed, std::make_unique<SelectGameModeCommand>(pIndicator.get(), 80.0f, true));
	input.BindCommand(0, GamePadButton::DPadUp, KeyState::Pressed, std::make_unique<SelectGameModeCommand>(pIndicator.get(), 80.0f, false));

	input.BindCommand(SDL_SCANCODE_DOWN, KeyState::Pressed, std::make_unique<SelectGameModeCommand>(pIndicator.get(), 80.0f, true));
	input.BindCommand(SDL_SCANCODE_UP, KeyState::Pressed, std::make_unique<SelectGameModeCommand>(pIndicator.get(), 80.0f, false));
	input.BindCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_unique<SelectGameModeCommand>(pIndicator.get(), 80.0f, true));
	input.BindCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_unique<SelectGameModeCommand>(pIndicator.get(), 80.0f, false));

	scene.Add(std::move(pIndicator));

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pSinglePlayer = std::make_unique<GameObject>("SinglePlayerLabel");
	pSinglePlayer->AddComponent<RenderComponent>("", true);
	pSinglePlayer->AddComponent<TextComponent>("Single player", font);
	pSinglePlayer->SetLocalPosition(300, 300);
	scene.Add(std::move(pSinglePlayer));

	auto pCoop = std::make_unique<GameObject>("CoopLabel");
	pCoop->AddComponent<RenderComponent>("", true);
	pCoop->AddComponent<TextComponent>("Co-op", font);
	pCoop->SetLocalPosition(300, 380);
	scene.Add(std::move(pCoop));

	auto pVersus = std::make_unique<GameObject>("VersusLabel");
	pVersus->AddComponent<RenderComponent>("", true);
	pVersus->AddComponent<TextComponent>("Versus", font);
	pVersus->SetLocalPosition(300, 460);
	scene.Add(std::move(pVersus));

	input.BindCommand(0, GamePadButton::Start, KeyState::Pressed, std::make_unique<StartGameModeCommand>());
	input.BindCommand(SDL_SCANCODE_RETURN, KeyState::Pressed, std::make_unique<StartGameModeCommand>());
}

void dae::GameModeSelectionState::UnbindCommands()
{
	auto& input = dae::InputManager::GetInstance();

	input.UnbindCommand(0, GamePadButton::DPadDown, KeyState::Pressed);
	input.UnbindCommand(0, GamePadButton::DPadUp, KeyState::Pressed);
	input.UnbindCommand(0, GamePadButton::Start, KeyState::Pressed);

	input.UnbindCommand(SDL_SCANCODE_DOWN, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_UP, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_S, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_W, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_RETURN, KeyState::Pressed);
}
