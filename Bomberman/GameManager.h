#pragma once
#include "Singleton.h"
#include <memory>
#include "States/GameState.h"

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

		int GetStageNumber() const { return m_stageNumber; }

	private:
		int m_stageNumber{ 1 };
		//int m_lives{ 3 };
		//int m_score{ 0 };

		void ChangeState(std::unique_ptr<GameState> state);
		std::unique_ptr<GameState> m_pCurrentGameState;
	};
}