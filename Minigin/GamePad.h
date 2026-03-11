#pragma once
#include <memory>

namespace dae
{
    enum class GamePadButton : uint16_t
    {
        DPadUp = 0x0001,
        DPadDown = 0x0002,
        DPadLeft = 0x0004,
        DPadRight = 0x0008,
        Start = 0x0010,
        Back = 0x0020,
        LeftThumb = 0x0040,
        RightThumb = 0x0080,
        LeftShoulder = 0x0100,
        RightShoulder = 0x0200,
        ButtonA = 0x1000,
        ButtonB = 0x2000,
        ButtonX = 0x4000,
        ButtonY = 0x8000
    };

    class GamePad final
    {
    public:
        explicit GamePad(uint16_t controllerIndex);
        ~GamePad();

        void Update();

        bool IsDownThisFrame(GamePadButton button) const;
        bool IsUpThisFrame(GamePadButton button) const;
        bool IsPressed(GamePadButton button) const;

    private:
        class GamePadImpl;
        std::unique_ptr<GamePadImpl> m_pImpl;
    };
};