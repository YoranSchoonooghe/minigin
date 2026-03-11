#pragma once
#include "Singleton.h"
#include "Commands/Command.h"
#include "GamePad.h"
#include <memory>
#include <vector>

namespace dae
{
	enum class KeyState
	{
		Down,
		Up,
		Pressed
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		explicit InputManager();
		~InputManager() = default;
		InputManager(const InputManager& other) = delete;
		InputManager(InputManager&& other) = delete;
		InputManager& operator=(const InputManager& other) = delete;
		InputManager& operator=(InputManager&& other) = delete;

		bool ProcessInput();

		void BindCommand(uint16_t controllerIndex, uint16_t button, KeyState state, std::unique_ptr<Command> command);
		void BindCommand(SDL_Scancode scancode, KeyState state, std::unique_ptr<Command> command);
		void UnBindCommand();

	private:
		struct ControllerBinding
		{
			uint16_t controllerIndex;
			uint16_t button;
			KeyState state;
			std::unique_ptr<Command> command;
		};

		struct KeyboardBinding {
			SDL_Scancode scancode;
			KeyState state;
			std::unique_ptr<Command> command;
		};

		std::vector<ControllerBinding> m_controllerBindings;
		std::vector<KeyboardBinding> m_keyboardBindings;

		std::vector<std::unique_ptr<GamePad>> m_pControllers;

		std::vector<uint8_t> m_previousKeyboardState;
	};

}
