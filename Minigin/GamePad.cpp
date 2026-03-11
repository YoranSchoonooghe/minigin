#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "GamePad.h"

namespace dae
{
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

        bool IsDownThisFrame(uint16_t button) const
        { 
            return m_buttonsPressedThisFrame & button; 
        }
        bool IsUpThisFrame(uint16_t button) const
        { 
            return m_buttonsReleasedThisFrame & button;
        }
        bool IsPressed(uint16_t button) const
        { 
            return m_currentState.Gamepad.wButtons & button;
        }

    private:
        uint16_t m_controllerIndex;

        XINPUT_STATE m_previousState{};
        XINPUT_STATE m_currentState{};

        WORD m_buttonsPressedThisFrame{};
        WORD m_buttonsReleasedThisFrame{};
    };


    GamePad::GamePad(uint16_t controllerIndex)
        : m_pImpl(std::make_unique<GamePadImpl>(controllerIndex))
    {
    }

    GamePad::~GamePad() = default;

    void GamePad::Update()
    {
        m_pImpl->Update();
    }

    bool GamePad::IsDownThisFrame(uint16_t button) const
    {
        return m_pImpl->IsDownThisFrame(button);
    }

    bool GamePad::IsUpThisFrame(uint16_t button) const
    {
        return m_pImpl->IsUpThisFrame(button);
    }

    bool GamePad::IsPressed(uint16_t button) const
    {
        return m_pImpl->IsPressed(button);
    }
}
