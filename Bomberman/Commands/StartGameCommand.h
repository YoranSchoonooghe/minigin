#pragma once
#include "Commands/Command.h"
#include "States/GameStateMachine.h"

namespace dae
{
	class StartGameCommand final : public Command
	{
	public:
		explicit StartGameCommand() {};

		void Execute() override
		{
			GameStateMachine::GetInstance().Play();
		}

	};
}