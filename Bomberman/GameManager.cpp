#include "GameManager.h"
#include "States/MainMenuState.h"
#include "States/PlayState.h"
#include "States/StageStartState.h"

void dae::GameManager::Init()
{
	m_pCurrentGameState = std::make_unique<StageStartState>(m_stageNumber);
	m_pCurrentGameState->Enter();

	m_grid = Grid(64.0f, 13, 31, glm::vec2(0.0f, 224.0f));
}

void dae::GameManager::Update(float deltaTime)
{
	auto pState = m_pCurrentGameState->Update(deltaTime);
	if (pState)
	{
		ChangeState(std::move(pState));
	}
}

void dae::GameManager::Play()
{
	ChangeState(std::make_unique<PlayState>());
}

void dae::GameManager::StartStage()
{
	ChangeState(std::make_unique<StageStartState>(m_stageNumber));
}

void dae::GameManager::ExitStage()
{
	++m_stageNumber;
	StartStage();
}

void dae::GameManager::RestartStage()
{
	--m_lives;
	StartStage();
}

void dae::GameManager::ChangeState(std::unique_ptr<GameState> state)
{
	if (m_pCurrentGameState)
	{
		m_pCurrentGameState->Exit();
	}

	m_pCurrentGameState = std::move(state);
	m_pCurrentGameState->Enter();
}