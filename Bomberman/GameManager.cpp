#include "GameManager.h"
#include "States/GameStateMachine.h"

void dae::GameManager::ExitStage()
{
	++m_stageNumber;
	GameStateMachine::GetInstance().StartStage();
}
