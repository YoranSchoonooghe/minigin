#include "GameStateMachine.h"
#include "MainMenuState.h"
#include "PlayState.h"

void dae::GameStateMachine::Init()
{
	m_pCurrentState = std::make_unique<MainMenuState>();
	m_pCurrentState->Enter();
}

void dae::GameStateMachine::Update(float deltaTime)
{
	auto pState = m_pCurrentState->Update(deltaTime);
	if (pState)
	{
		ChangeState(std::move(pState));
	}
}

void dae::GameStateMachine::Play()
{
	ChangeState(std::make_unique<PlayState>());
}

void dae::GameStateMachine::ChangeState(std::unique_ptr<GameState> state)
{
	if (m_pCurrentState)
	{
		m_pCurrentState->Exit();
	}

	m_pCurrentState = std::move(state);
	m_pCurrentState->Enter();
}
