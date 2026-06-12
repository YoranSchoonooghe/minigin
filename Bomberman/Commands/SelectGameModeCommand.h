#pragma once
#include "Commands/Command.h"
#include "GameObject.h"
#include "GameManager.h"

namespace dae
{
	class SelectGameModeCommand final : public Command
	{
	public:
		explicit SelectGameModeCommand(GameObject* pIndicator, float stepSize, bool moveDown = true)
			: m_pIndicator{ pIndicator }
			, m_stepSize{ stepSize }
			, m_moveDown{ moveDown }
		{
		}

		void Execute() override
		{
			if (m_moveDown)
				MoveDown();
			else
				MoveUp();
		}

	private:
		void MoveDown()
		{
			auto position = m_pIndicator->GetLocalPosition();

			auto gameMode = GameManager::GetInstance().GetGameMode();

			if (gameMode == GameMode::Versus)
			{
				position.y -= 2 * m_stepSize;
				m_pIndicator->SetLocalPosition(position);

				GameManager::GetInstance().SetGameMode(GameMode::SinglePlayer);

				return;
			}

			position.y += m_stepSize;
			m_pIndicator->SetLocalPosition(position);

			gameMode = static_cast<GameMode>(static_cast<int>(gameMode) + 1);
			GameManager::GetInstance().SetGameMode(gameMode);
		}

		void MoveUp()
		{
			auto position = m_pIndicator->GetLocalPosition();

			auto gameMode = GameManager::GetInstance().GetGameMode();

			if (gameMode == GameMode::SinglePlayer)
			{
				position.y += 2 * m_stepSize;
				m_pIndicator->SetLocalPosition(position);

				GameManager::GetInstance().SetGameMode(GameMode::Versus);

				return;
			}

			position.y -= m_stepSize;
			m_pIndicator->SetLocalPosition(position);

			gameMode = static_cast<GameMode>(static_cast<int>(gameMode) - 1);
			GameManager::GetInstance().SetGameMode(gameMode);
		}

		GameObject* m_pIndicator;
		float m_stepSize;
		bool m_moveDown;

	};
}