#pragma once
#include "Commands/Command.h"
#include "GameManager.h"

namespace dae
{
	class StartGameCommand final : public Command
	{
	public:
		explicit StartGameCommand() {};

		void Execute() override
		{
			GameManager::GetInstance().StartStage();
		}

	};
}