#pragma once
#include "GameState.h"

namespace dae
{
	class PlayState final : public GameState
	{
	public:

		void Enter() override;
		void Exit() override;

	private:
		void LoadScene();
		void UnbindCommands();

		int m_enemiesCount{ 0 };
	};
}