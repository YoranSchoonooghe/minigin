#pragma once
#include "Commands/Command.h"
#include "GameManager.h"

namespace dae
{
	class MainMenuCommand final : public Command
	{
	public:
		explicit MainMenuCommand() {};

		void Execute() override
		{
			GameManager::GetInstance().GoToMainMenu();
		}

	};
}