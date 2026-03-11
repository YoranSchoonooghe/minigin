#pragma once
#include <memory>

namespace dae
{
	class GamePad final
	{
	public:
		explicit GamePad(uint16_t controllerIndex);
		~GamePad();

		void Update();
		
		bool IsDownThisFrame(uint16_t button) const;
		bool IsUpThisFrame(uint16_t button) const;
		bool IsPressed(uint16_t button) const;

	private:
		class GamePadImpl;
		std::unique_ptr<GamePadImpl> m_pImpl;
	};
}