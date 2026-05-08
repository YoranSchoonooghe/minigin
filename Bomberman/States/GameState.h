#pragma once
#include <memory>

namespace dae
{
	class GameState
	{
	public:
		virtual ~GameState() = default;

		virtual std::unique_ptr<GameState> Update(float) { return nullptr; }
		virtual void Enter() {};
		virtual void Exit() {};
	};
}