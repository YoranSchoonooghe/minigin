#pragma once
#include "Commands/Command.h"
#include "GameObject.h"
#include "Scene.h"
#include "Components/BombComponent.h"
#include <cmath>
#include "Utils.h"
#include <vector>
#include "Audio/ServiceLocator.h"
#include "GameManager.h"

namespace dae
{
	class DropBombCommand final : public Command
	{
	public:
		explicit DropBombCommand(GameObject* pBomberman, std::vector<GameObject*>& bombsPool)
			: m_pBomberman{ pBomberman }
			, m_bombsPool{ bombsPool }
		{
		}

		void Execute() override
		{
			auto position{ m_pBomberman->GetWorldPosition() };
			//SnapToGrid(position, 64.0f);
			GridUtils::SnapToGrid(GameManager::GetInstance().GetGrid(), position);

			int nrOfBombs{ 0 };
			for (auto* pBomb : m_bombsPool)
			{
				if (!pBomb->IsActive()) continue;

				++nrOfBombs;
			}

			int maxBombs = GameManager::GetInstance().GetPowerUpData().nrOfBombs;
			//if (GameManager::GetInstance().GetGameMode() == GameMode::CoOp)
			//{
			//	maxBombs *= 2;
			//}

			if (nrOfBombs >= maxBombs) return;

			for (auto* pBomb : m_bombsPool)
			{
				if (pBomb->IsActive()) continue;

				ServiceLocator::GetSoundSystem().Play(2);

				pBomb->SetLocalPosition(position.x, position.y);
				auto* pTimer = pBomb->GetComponent<TimerComponent>();
				pTimer->Restart();
				pBomb->SetActive(true);

				return;
			}
		}

	private:
		//void SnapToGrid(glm::vec3& position, float gridSize)
		//{
		//	position.x = std::roundf(position.x / gridSize) * gridSize;
		//	position.y = std::roundf((position.y - 224.0f) / gridSize) * gridSize + 224.0f;
		//}

		GameObject* m_pBomberman;
		std::vector<GameObject*>& m_bombsPool;
	};
}