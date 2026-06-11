#pragma once
#include "GameState.h"
#include "Events/Observer.h"

namespace dae
{
	class ExitComponent;

	class PlayState final : public GameState, public Observer
	{
	public:

		void Enter() override;
		void Exit() override;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void LoadScene();
		void UnbindCommands();

		int m_enemiesCount{ 0 };
		ExitComponent* m_pExit{ nullptr };
	};
}