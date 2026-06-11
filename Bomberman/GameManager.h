#pragma once
#include "Singleton.h"
#include <memory>
#include "States/GameState.h"
#include "Grid.h"

namespace dae
{
	class GameManager final : public Singleton<GameManager>
	{
	public:
		void Init();
		void Update(float deltaTime);

		void Play();
		void StartStage();
		void ExitStage();
		void RestartStage();

		Grid GetGrid() const { return m_grid; }
		int GetLives() const { return m_lives; }
		int GetScore() const { return m_score; }
		void AddPoints(int points) { m_score += points; }

	private:
		friend class Singleton<GameManager>;
		GameManager() = default;

		void ChangeState(std::unique_ptr<GameState> state);

		std::unique_ptr<GameState> m_pCurrentGameState;

		Grid m_grid{};
		int m_stageNumber{ 1 };
		int m_lives{ 3 };
		int m_score{ 0 };

	};
}