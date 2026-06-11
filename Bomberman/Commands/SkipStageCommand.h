#pragma once
#include "Commands/Command.h"
#include "GameManager.h"

namespace dae
{
	class SkipStageCommand final : public Command
	{
	public:
		explicit SkipStageCommand() = default;

		void Execute() override
		{
			GameManager::GetInstance().ExitStage();
		}
	};
}