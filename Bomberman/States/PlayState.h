#pragma once
#include "GameState.h"
#include "Events/Observer.h"
#include <vector>

namespace dae
{
	class ExitComponent;

	class PlayState final : public GameState, public Observer
	{
	public:
		explicit PlayState(int stageNumber);
		~PlayState() = default;
		PlayState(const PlayState& other) = delete;
		PlayState(PlayState&& other) = delete;
		PlayState& operator=(const PlayState& other) = delete;
		PlayState& operator=(PlayState&& other) = delete;

		void Enter() override;
		void Exit() override;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void LoadScene();
		void UnbindCommands();

		int m_stageNumber;
		int m_enemiesCount{ 0 };
		ExitComponent* m_pExit{ nullptr };
		std::vector<GameObject*> m_bombsPool;
	};
}