#include "GamePad.h"
#include <vector>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <XInput.h>
    #pragma comment(lib, "xinput.lib")
#else
    #include <SDL3/SDL.h>
#endif

namespace dae
{
#ifdef _WIN32
    class GamePad::GamePadImpl
    {
    public:
        explicit GamePadImpl(uint16_t controllerIndex)
            : m_controllerIndex(controllerIndex)
        {
            ZeroMemory(&m_previousState, sizeof(XINPUT_STATE));
            ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
        }

        void Update()
        {
            CopyMemory(&m_previousState, &m_currentState, sizeof(XINPUT_STATE));
            ZeroMemory(&m_currentState, sizeof(XINPUT_STATE));
            XInputGetState(m_controllerIndex, &m_currentState);

            auto buttonChanges = m_currentState.Gamepad.wButtons ^ m_previousState.Gamepad.wButtons;
            m_buttonsPressedThisFrame = buttonChanges & m_currentState.Gamepad.wButtons;
            m_buttonsReleasedThisFrame = buttonChanges & (~m_currentState.Gamepad.wButtons);
        }

        bool IsDownThisFrame(GamePadButton button) const
        { 
            return m_buttonsPressedThisFrame & static_cast<uint16_t>(button); 
        }
        bool IsUpThisFrame(GamePadButton button) const
        { 
            return m_buttonsReleasedThisFrame & static_cast<uint16_t>(button);
        }
        bool IsPressed(GamePadButton button) const
        { 
            return m_currentState.Gamepad.wButtons & static_cast<uint16_t>(button);
        }

    private:
        uint16_t m_controllerIndex;

        XINPUT_STATE m_previousState{};
        XINPUT_STATE m_currentState{};

        WORD m_buttonsPressedThisFrame{};
        WORD m_buttonsReleasedThisFrame{};
    };

#else
    class GamePad::GamePadImpl
    {
    public:
        explicit GamePadImpl(uint16_t controllerIndex)
            : m_controllerIndex(controllerIndex)
            , m_previousButtons(static_cast<size_t>(SDL_GAMEPAD_BUTTON_COUNT), false)
            , m_currentButtons(static_cast<size_t>(SDL_GAMEPAD_BUTTON_COUNT), false)
        {
            int count;
            auto gamepads = SDL_GetGamepads(&count);

            if (controllerIndex < (uint16_t)count)
            {
                m_pGamepad = SDL_OpenGamepad(gamepads[controllerIndex]);
            }

            SDL_free(gamepads);
        }

        ~GamePadImpl()
        {
            if (m_pGamepad)
            {
                SDL_CloseGamepad(m_pGamepad);
            }
        }

        void Update()
        {
            if (!m_pGamepad) return;

            m_previousButtons = m_currentButtons;

            for (int index = 0; index < SDL_GAMEPAD_BUTTON_COUNT; ++index)
            {
                m_currentButtons[index] = SDL_GetGamepadButton(m_pGamepad, (SDL_GamepadButton)index);
            }
        }

        bool IsDownThisFrame(GamePadButton button) const
        {
            int index = static_cast<int>(GetSDLButton(button));
            return m_currentButtons[index] && !m_previousButtons[index];
        }
        bool IsUpThisFrame(GamePadButton button) const
        {
            int index = static_cast<int>(GetSDLButton(button));;
            return !m_currentButtons[index] && m_previousButtons[index];
        }
        bool IsPressed(GamePadButton button) const
        {
            return m_currentButtons[static_cast<int>(GetSDLButton(button))];
        }

    private:
        SDL_GamepadButton GetSDLButton(GamePadButton button) const
        {
            switch (button)
            {
            case GamePadButton::DPadUp:
                return SDL_GAMEPAD_BUTTON_DPAD_UP;
            case GamePadButton::DPadLeft:
                return SDL_GAMEPAD_BUTTON_DPAD_LEFT;
            case GamePadButton::DPadDown:
                return SDL_GAMEPAD_BUTTON_DPAD_DOWN;
            case GamePadButton::DPadRight:
                return SDL_GAMEPAD_BUTTON_DPAD_RIGHT;
            case GamePadButton::Start:
                return SDL_GAMEPAD_BUTTON_START;
            case GamePadButton::Back:
                return SDL_GAMEPAD_BUTTON_BACK;
            case GamePadButton::LeftThumb:
                return SDL_GAMEPAD_BUTTON_LEFT_STICK;
            case GamePadButton::RightThumb:
                return SDL_GAMEPAD_BUTTON_RIGHT_STICK;
            case GamePadButton::LeftShoulder:
                return SDL_GAMEPAD_BUTTON_LEFT_SHOULDER;
            case GamePadButton::RightShoulder:
                return SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER;
            case GamePadButton::ButtonA:
                return SDL_GAMEPAD_BUTTON_SOUTH;
            case GamePadButton::ButtonB:
                return SDL_GAMEPAD_BUTTON_EAST;
            case GamePadButton::ButtonX:
                return SDL_GAMEPAD_BUTTON_WEST;
            case GamePadButton::ButtonY:
                return SDL_GAMEPAD_BUTTON_NORTH;
            default:
                return SDL_GAMEPAD_BUTTON_INVALID;
            }
        }

        uint16_t m_controllerIndex;

        SDL_Gamepad* m_pGamepad = nullptr;

        std::vector<bool> m_previousButtons;
        std::vector<bool> m_currentButtons;
    };
#endif
    GamePad::GamePad(uint16_t controllerIndex)
        : m_pImpl(std::make_unique<GamePadImpl>(controllerIndex))
    {
    }

    GamePad::~GamePad() = default;

    void GamePad::Update()
    {
        m_pImpl->Update();
    }

    bool GamePad::IsDownThisFrame(GamePadButton button) const
    {
        return m_pImpl->IsDownThisFrame(button);
    }

    bool GamePad::IsUpThisFrame(GamePadButton button) const
    {
        return m_pImpl->IsUpThisFrame(button);
    }

    bool GamePad::IsPressed(GamePadButton button) const
    {
        return m_pImpl->IsPressed(button);
    }
}
