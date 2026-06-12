#pragma once
#include "Singleton.h"
#include <memory>
#include "States/GameState.h"
#include "Grid.h"

namespace dae
{
	struct PowerUpData
	{
		int nrOfBombs = 1;
		int flameRange = 1;
		bool hasDetonator = false;
	};

	enum class GameMode
	{
		SinglePlayer,
		CoOp,
		Versus
	};

	class GameManager final : public Singleton<GameManager>
	{
	public:
		void Init();
		void Update(float deltaTime);

		void GoToGameModeSelection();
		void StartGame();
		void StartStage();
		void PlayStage();
		void ExitStage();
		void RestartStage();

		Grid GetGrid() const { return m_grid; }
		int GetLives() const { return m_lives; }
		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }
		PowerUpData GetPowerUpData() const { return m_powerUpData; }
		void SetPowerUpData(const PowerUpData& powerUpData) { m_powerUpData = powerUpData; }

		GameMode GetGameMode() const { return m_selectedGameMode; }
		void SetGameMode(GameMode gameMode) { m_selectedGameMode = gameMode; }

	private:
		friend class Singleton<GameManager>;
		GameManager() = default;

		void ChangeState(std::unique_ptr<GameState> state);

		std::unique_ptr<GameState> m_pCurrentGameState;

		GameMode m_selectedGameMode{ GameMode::SinglePlayer };

		Grid m_grid{};
		int m_stageNumber{ 1 };
		int m_lives{ 3 };
		int m_score{ 0 };
		PowerUpData m_powerUpData{};
	};
}