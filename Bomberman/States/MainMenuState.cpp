#include "MainMenuState.h"
#include <SDL3/SDL.h>
#include "Renderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Components/RenderComponent.h"
#include "Commands/StartGameCommand.h"
#include "Audio/ServiceLocator.h"

void dae::MainMenuState::Enter()
{
	LoadScene();
}

void dae::MainMenuState::Exit()
{
	dae::ServiceLocator::GetSoundSystem().StopAll();
	UnbindCommands();
}

void dae::MainMenuState::LoadScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();
	auto& input = dae::InputManager::GetInstance();

	dae::Renderer::GetInstance().SetBackgroundColor({ 0, 0, 0, 255 });

	auto pMainMenuScreen = std::make_unique<dae::GameObject>("MainMenuScreen");
	pMainMenuScreen->AddComponent<dae::RenderComponent>("MainMenu.png", true);
	scene.Add(std::move(pMainMenuScreen));

	input.BindCommand(SDL_SCANCODE_RETURN, dae::KeyState::Pressed, std::make_unique<dae::StartGameCommand>());
	input.BindCommand(0, dae::GamePadButton::Start, dae::KeyState::Pressed, std::make_unique<dae::StartGameCommand>());

	dae::ServiceLocator::GetSoundSystem().AddAudioSource(dae::AudioSource(6, "Audio/MainMenuMusic.mp3"));
	dae::ServiceLocator::GetSoundSystem().Play(6);
}

void dae::MainMenuState::UnbindCommands()
{
	auto& input = dae::InputManager::GetInstance();

	input.UnbindCommand(SDL_SCANCODE_RETURN, dae::KeyState::Pressed);
	input.UnbindCommand(0, dae::GamePadButton::Start, dae::KeyState::Pressed);
}
