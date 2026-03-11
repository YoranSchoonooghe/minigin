#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"

#if WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <Xinput.h>
#endif

dae::InputManager::InputManager()
{
	const int MAX_CONTROLLERS{ 4 };
	m_pControllers.reserve(MAX_CONTROLLERS);

	for (int index{ 0 }; index < MAX_CONTROLLERS; ++index)
	{
		m_pControllers.emplace_back(std::make_unique<GamePad>(index));
	}
}

bool dae::InputManager::ProcessInput()
{
    int numKeys;
    const bool* pCurrentKeyboardState = SDL_GetKeyboardState(&numKeys);

    if (m_previousKeyboardState.empty())
    {
        m_previousKeyboardState.assign(numKeys, 0);
    }

    SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}
		if (e.type == SDL_EVENT_KEY_DOWN) {
			
		}
		if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			
		}
		// etc...

		//process event for IMGUI
		ImGui_ImplSDL3_ProcessEvent(&e);
	}

    for (const auto& pController : m_pControllers)
    {
        pController->Update();
    }

    for (const auto& binding : m_controllerBindings)
    {
        auto& gamepad = m_pControllers[binding.controllerIndex];

        switch (binding.state)
        {
        case KeyState::Pressed:
            if (gamepad->IsDownThisFrame(binding.button))
            {
                binding.command->Execute();
            }
            break;
        case KeyState::Down:
            if (gamepad->IsPressed(binding.button))
            {
                binding.command->Execute();
            }
            break;
        case KeyState::Up:
            if (gamepad->IsUpThisFrame(binding.button))
            {
                binding.command->Execute();
            }
            break;
        }
    }

    for (const auto& binding : m_keyboardBindings)
    {
        bool isDown = pCurrentKeyboardState[binding.scancode];
        bool wasDown = m_previousKeyboardState[binding.scancode];

        switch (binding.state)
        {
        case KeyState::Pressed:
            if (isDown && !wasDown) binding.command->Execute();
            break;
        case KeyState::Down:
            if (isDown) binding.command->Execute();
            break;
        case KeyState::Up:
            if (!isDown && wasDown) binding.command->Execute();
            break;
        }
    }

    std::copy(pCurrentKeyboardState, pCurrentKeyboardState + numKeys, m_previousKeyboardState.begin());

	return true;
}

void dae::InputManager::BindCommand(uint16_t controllerIndex, uint16_t button, KeyState state, std::unique_ptr<Command> command)
{
    m_controllerBindings.push_back({ controllerIndex, button, state, std::move(command) });
}

void dae::InputManager::BindCommand(SDL_Scancode scancode, KeyState state, std::unique_ptr<Command> command)
{

    m_keyboardBindings.push_back({ scancode, state, std::move(command) });
}
