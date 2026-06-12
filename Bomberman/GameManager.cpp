#include "GameManager.h"
#include "States/MainMenuState.h"
#include "States/PlayState.h"
#include "States/StageStartState.h"
#include "States/NameEntryState.h"
#include "States/GameModeSelectionState.h"
#include "States/HighScoreMenuState.h"
#include "ResourceManager.h"

void dae::GameManager::Init()
{
	m_pCurrentGameState = std::make_unique<MainMenuState>();
	//m_pCurrentGameState = std::make_unique<GameModeSelectionState>();
	//m_pCurrentGameState = std::make_unique<StageStartState>(m_stageNumber);
	//m_pCurrentGameState = std::make_unique<NameEntryState>();
	//m_pCurrentGameState = std::make_unique<HighScoreMenuState>();
	m_pCurrentGameState->Enter();

	m_grid = Grid(64.0f, 13, 31, glm::vec2(0.0f, 224.0f));
	
	m_highscores = HighScoreLoader::LoadHighScores(ResourceManager::GetInstance().GetDataPath() / "HighScores.json");
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
		StartStage();
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
	ChangeState(std::make_unique<PlayState>(m_stageNumber));
}

void dae::GameManager::ExitStage()
{
	if (m_stageNumber == 3)
	{
		EndGame();
	}
	else
	{
		++m_stageNumber;
		StartStage();
	}
}

void dae::GameManager::RestartStage()
{
	--m_lives;
	if (m_lives < 0)
	{
		EndGame();
	}
	else
	{
		m_powerUpData.nrOfBombs = 1;
		m_powerUpData.flameRange = 1;
		m_powerUpData.hasDetonator = false;

		StartStage();
	}
}

void dae::GameManager::ShowHighScores()
{
	ChangeState(std::make_unique<HighScoreMenuState>());
}

void dae::GameManager::GoToMainMenu()
{
	m_powerUpData.nrOfBombs = 1;
	m_powerUpData.flameRange = 1;
	m_powerUpData.hasDetonator = false;
	m_lives = 3;
	m_score = 0;
	m_stageNumber = 1;
	m_selectedGameMode = GameMode::SinglePlayer;

	ChangeState(std::make_unique<MainMenuState>());
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

void dae::GameManager::EndGame()
{
	if (m_score > m_highscores[m_highscores.size() - 1].score)
	{
		ChangeState(std::make_unique<NameEntryState>());
	}
	else
	{
		ChangeState(std::make_unique<HighScoreMenuState>());
	}
}

void dae::GameManager::SaveHighScores(const std::filesystem::path& filePath)
{
	json jsonData = m_highscores;

	std::ofstream file(filePath);

	if (!file.is_open())
	{
		std::cout << "Failed to open highscore file for writing\n";
		return;
	}

	file << jsonData.dump(4);
}

void dae::GameManager::AddHighScore(const std::string& name)
{
	auto maxSize = m_highscores.size();

	m_highscores.push_back(HighScore(name, m_score));

	std::sort(m_highscores.begin(), m_highscores.end(),
		[](const HighScore& a, const HighScore& b)
		{
			return a.score > b.score;
		});

	m_highscores.resize(maxSize);

	//SaveHighScores(ResourceManager::GetInstance().GetDataPath()/"HighScores.json");
}
