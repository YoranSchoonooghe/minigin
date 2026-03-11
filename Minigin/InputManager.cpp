#include <SDL3/SDL.h>
#include <backends/imgui_impl_sdl3.h>
#include "InputManager.h"

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
    SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_EVENT_QUIT) {
			return false;
		}

		ImGui_ImplSDL3_ProcessEvent(&e);
	}

    ProcessControllerInput();
    ProcessKeyboardInput();

	return true;
}

void dae::InputManager::BindCommand(uint16_t controllerIndex, dae::GamePadButton button, KeyState state, std::unique_ptr<Command> command)
{
    m_controllerBindings.push_back({ controllerIndex, button, state, std::move(command) });
}

void dae::InputManager::BindCommand(SDL_Scancode scancode, KeyState state, std::unique_ptr<Command> command)
{

    m_keyboardBindings.push_back({ scancode, state, std::move(command) });
}

void dae::InputManager::UnbindCommand(uint16_t controllerIndex, dae::GamePadButton button, KeyState state)
{
    std::erase_if(m_controllerBindings,
        [controllerIndex, button, state](const ControllerBinding& binding)
        {
            return binding.controllerIndex == controllerIndex &&
                binding.button == button &&
                binding.state == state;
        });
}

void dae::InputManager::UnbindCommand(SDL_Scancode scancode, KeyState state)
{
    std::erase_if(m_keyboardBindings,
        [scancode, state](const KeyboardBinding& binding)
        {
            return binding.scancode == scancode && binding.state == state;
        }
    );
}

void dae::InputManager::ProcessControllerInput()
{
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
}

void dae::InputManager::ProcessKeyboardInput()
{
    int numKeys;
    const bool* pCurrentKeyboardState = SDL_GetKeyboardState(&numKeys);

    if (m_previousKeyboardState.empty())
    {
        m_previousKeyboardState.assign(numKeys, 0);
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
}
