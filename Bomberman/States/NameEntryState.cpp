#include "NameEntryState.h"
#include <SDL3/SDL.h>
#include "SceneManager.h"
#include "InputManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Components/RenderComponent.h"
#include "Components/TextComponent.h"
#include "Components/NameEntryComponent.h"
#include "Commands/ChangeCharacterCommand.h"
#include "Commands/ChangeSlotCommand.h"
#include "GameManager.h"

dae::NameEntryState::~NameEntryState()
{
	if (m_pNameEntrySubject)
	{
		m_pNameEntrySubject->RemoveObserver(this);
	}
}

void dae::NameEntryState::Enter()
{
	LoadScene();
}

void dae::NameEntryState::Exit()
{
	UnbindCommands();
}

void dae::NameEntryState::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnNameEntered"):
		GameManager::GetInstance().AddHighScore(m_pNameEntryComponent->GetName());
		GameManager::GetInstance().ShowHighScores();
		break;
	}
}

void dae::NameEntryState::LoadScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene();
	auto& input = InputManager::GetInstance();

	dae::Renderer::GetInstance().SetBackgroundColor({ 0, 0, 0, 255 });

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pEnterNameLabel = std::make_unique<GameObject>("EnterNameLabel");
	pEnterNameLabel->AddComponent<RenderComponent>("", true);
	pEnterNameLabel->AddComponent<TextComponent>("Enter Your Name ", font);
	pEnterNameLabel->SetLocalPosition(200, 160);
	scene.Add(std::move(pEnterNameLabel));

	auto inputFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto pCharacterInputLabel = std::make_unique<GameObject>("CharacterInputLabel");
	pCharacterInputLabel->AddComponent<RenderComponent>("", true);
	pCharacterInputLabel->AddComponent<TextComponent>("Use Up/Down to change character.", inputFont);
	pCharacterInputLabel->SetLocalPosition(200, 210);
	scene.Add(std::move(pCharacterInputLabel));

	auto pIndexInputLabel = std::make_unique<GameObject>("IndexInputLabel");
	pIndexInputLabel->AddComponent<RenderComponent>("", true);
	pIndexInputLabel->AddComponent<TextComponent>("Press A/Enter to proceed.", inputFont);
	pIndexInputLabel->SetLocalPosition(200, 240);
	scene.Add(std::move(pIndexInputLabel));

	auto characterFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 128);
	auto pNameEntry = std::make_unique<GameObject>("NameEntry");
	pNameEntry->AddComponent<RenderComponent>("", true);
	pNameEntry->AddComponent<TextComponent>("", characterFont);
	m_pNameEntryComponent = pNameEntry->AddComponent<NameEntryComponent>();
	m_pNameEntrySubject = m_pNameEntryComponent->GetSubject();
	m_pNameEntrySubject->AddObserver(this);
	pNameEntry->SetLocalPosition(360, 500);

	input.BindCommand(0, GamePadButton::DPadDown, KeyState::Pressed, std::make_unique<ChangeCharacterCommand>(pNameEntry.get(), true));
	input.BindCommand(0, GamePadButton::DPadUp, KeyState::Pressed, std::make_unique<ChangeCharacterCommand>(pNameEntry.get(), false));
	input.BindCommand(SDL_SCANCODE_DOWN, KeyState::Pressed, std::make_unique<ChangeCharacterCommand>(pNameEntry.get(), true));
	input.BindCommand(SDL_SCANCODE_UP, KeyState::Pressed, std::make_unique<ChangeCharacterCommand>(pNameEntry.get(), false));
	input.BindCommand(SDL_SCANCODE_S, KeyState::Pressed, std::make_unique<ChangeCharacterCommand>(pNameEntry.get(), true));
	input.BindCommand(SDL_SCANCODE_W, KeyState::Pressed, std::make_unique<ChangeCharacterCommand>(pNameEntry.get(), false));

	input.BindCommand(0, GamePadButton::ButtonA, KeyState::Pressed, std::make_unique<ChangeSlotCommand>(pNameEntry.get()));
	input.BindCommand(SDL_SCANCODE_RETURN, KeyState::Pressed, std::make_unique<ChangeSlotCommand>(pNameEntry.get()));

	scene.Add(std::move(pNameEntry));

}

void dae::NameEntryState::UnbindCommands()
{
	auto& input = InputManager::GetInstance();

	input.UnbindCommand(0, GamePadButton::DPadDown, KeyState::Pressed);
	input.UnbindCommand(0, GamePadButton::DPadUp, KeyState::Pressed);
	input.UnbindCommand(0, GamePadButton::ButtonA, KeyState::Pressed);

	input.UnbindCommand(SDL_SCANCODE_DOWN, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_UP, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_S, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_W, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_RETURN, KeyState::Pressed);
}
