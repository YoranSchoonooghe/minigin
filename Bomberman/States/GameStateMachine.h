#pragma once
#include "Singleton.h"
#include <memory>
#include "GameState.h"

namespace dae
{
	class GameStateMachine final : public Singleton<GameStateMachine>
	{
	public:
		void Init();
		void Update(float deltaTime);

		void Play();
		void StartStage();

	private:
		void ChangeState(std::unique_ptr<GameState> state);
		std::unique_ptr<GameState> m_pCurrentState;
	};
}