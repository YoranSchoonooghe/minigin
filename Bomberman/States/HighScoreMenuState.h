#pragma once
#include "GameState.h"

namespace dae
{
	class Subject;

	class HighScoreMenuState final : public GameState
	{
	public:
		explicit HighScoreMenuState() = default;
		~HighScoreMenuState() = default;
		HighScoreMenuState(const HighScoreMenuState& other) = delete;
		HighScoreMenuState(HighScoreMenuState&& other) = delete;
		HighScoreMenuState& operator=(const HighScoreMenuState& other) = delete;
		HighScoreMenuState& operator=(HighScoreMenuState&& other) = delete;

		void Enter() override;
		void Exit() override;

	private:
		void LoadScene();
		void UnbindCommands();

	};
}