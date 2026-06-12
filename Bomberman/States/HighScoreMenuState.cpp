#include "HighScoreMenuState.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Components/RenderComponent.h"
#include "Components/TextComponent.h"
#include "HighScoreLoader.h"
#include "GameManager.h"
#include "Commands/MainMenuCommand.h"

void dae::HighScoreMenuState::Enter()
{
	//TEMP
	//auto highscores = HighScoreLoader::LoadHighScores(ResourceManager::GetInstance().GetDataPath() / "HighScores.json");
	//GameManager::GetInstance().SetHighScores(highscores);

	LoadScene();
}

void dae::HighScoreMenuState::Exit()
{
	UnbindCommands();
}

void dae::HighScoreMenuState::LoadScene()
{
	auto& scene = SceneManager::GetInstance().CreateScene();
	auto& input = InputManager::GetInstance();

	Renderer::GetInstance().SetBackgroundColor({ 0, 0, 0, 255 });

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pGameOverLabel = std::make_unique<dae::GameObject>("GameOverLabel");
	pGameOverLabel->AddComponent<RenderComponent>("", true);
	pGameOverLabel->AddComponent<TextComponent>("GAME OVER", font);
	pGameOverLabel->SetLocalPosition(200, 160);
	scene.Add(std::move(pGameOverLabel));

	auto pHighScoresLabel = std::make_unique<dae::GameObject>("HighScoresLabel");
	pHighScoresLabel->AddComponent<RenderComponent>("", true);
	pHighScoresLabel->AddComponent<TextComponent>("High Scores", font);
	pHighScoresLabel->SetLocalPosition(200, 300);
	scene.Add(std::move(pHighScoresLabel));

	auto highScores = GameManager::GetInstance().GetHighScores();

	for (size_t index{ 0 }; index < highScores.size(); ++index)
	{
		auto pLeaderboardEntry = std::make_unique<dae::GameObject>("Leaderboard");
		pLeaderboardEntry->AddComponent<RenderComponent>("", true);
		pLeaderboardEntry->AddComponent<TextComponent>(
			std::to_string(index + 1) + ". " + highScores[index].name
			+ "                  " + std::to_string(highScores[index].score),
			font);
		pLeaderboardEntry->SetLocalPosition(200, 350 + index * 50.0f);
		scene.Add(std::move(pLeaderboardEntry));
	}

	input.BindCommand(0, GamePadButton::ButtonA, KeyState::Pressed, std::make_unique<MainMenuCommand>());
	input.BindCommand(SDL_SCANCODE_RETURN, KeyState::Pressed, std::make_unique<MainMenuCommand>());
}

void dae::HighScoreMenuState::UnbindCommands()
{
	auto& input = InputManager::GetInstance();

	input.UnbindCommand(0, GamePadButton::ButtonA, KeyState::Pressed);
	input.UnbindCommand(SDL_SCANCODE_RETURN, KeyState::Pressed);
}

