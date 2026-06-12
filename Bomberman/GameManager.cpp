#include "GameManager.h"
#include "States/MainMenuState.h"
#include "States/PlayState.h"
#include "States/StageStartState.h"
//#include "States/HighScoreState.h"
#include "States/GameModeSelectionState.h"

void dae::GameManager::Init()
{
	m_pCurrentGameState = std::make_unique<MainMenuState>();
	//m_pCurrentGameState = std::make_unique<HighScoreState>();
	//m_pCurrentGameState = std::make_unique<GameModeSelectionState>();
	//m_pCurrentGameState = std::make_unique<StageStartState>(m_stageNumber);
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

void dae::GameManager::GoToGameModeSelection()
{
	ChangeState(std::make_unique<GameModeSelectionState>());
}

void dae::GameManager::StartGame()
{
	switch (m_selectedGameMode)
	{
	case dae::GameMode::SinglePlayer:
		StartStage();
		break;
	case dae::GameMode::CoOp:
		break;
	case dae::GameMode::Versus:
		break;
	}
}

void dae::GameManager::StartStage()
{
	ChangeState(std::make_unique<StageStartState>(m_stageNumber));
}

void dae::GameManager::PlayStage()
{
	ChangeState(std::make_unique<PlayState>());
}

void dae::GameManager::ExitStage()
{
	++m_stageNumber;
	StartStage();
}

void dae::GameManager::RestartStage()
{
	--m_lives;
	if (m_lives < 0)
	{
		
	}
	else
	{
		m_powerUpData.nrOfBombs = 1;
		m_powerUpData.flameRange = 1;
		m_powerUpData.hasDetonator = false;

		StartStage();
	}
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