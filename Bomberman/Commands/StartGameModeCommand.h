#pragma once
#include "Commands/Command.h"
#include "GameManager.h"

namespace dae
{
	class StartGameModeCommand final : public Command
	{
	public:
		explicit StartGameModeCommand() {};

		void Execute() override
		{
			GameManager::GetInstance().StartGame();
		}

	};
}