#pragma once
#include "GameState.h"

namespace dae
{
	class MainMenuState final : public GameState
	{
	public:

		void Enter() override;
		void Exit() override;

	private:
		void LoadScene();
		void UnbindCommands();
		void LoadHighScores();
	};
}