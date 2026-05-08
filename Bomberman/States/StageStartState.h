#pragma once
#include "GameState.h"
#include "Events/Observer.h"

namespace dae
{
	class Subject;

	class StageStartState final : public GameState, public Observer
	{
	public:
		explicit StageStartState(int stageNumber);
		~StageStartState();
		StageStartState(const StageStartState& other) = delete;
		StageStartState(StageStartState&& other) = delete;
		StageStartState& operator=(const StageStartState& other) = delete;
		StageStartState& operator=(StageStartState&& other) = delete;

		void Enter() override;
		void Exit() override;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void LoadScene();

		int m_stageNumber;
		float m_timeToStart{ 3.0f };

		Subject* m_pTimerComponentSubject{ nullptr };
	};
}