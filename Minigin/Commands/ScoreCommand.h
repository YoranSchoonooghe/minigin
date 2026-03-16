#pragma once
#include "Command.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include <cassert>

namespace dae
{
	class ScoreCommand : public Command
	{
	public:
		explicit ScoreCommand(GameObject* pGameObject, int score = 100)
			: m_score{ score }
		{
			m_pScoreComponent = pGameObject->GetComponent<ScoreComponent>();

			assert(m_pScoreComponent != nullptr && "ScoreCommand: GameObject is missing a ScoreComponent!");
		}

		void Execute() override
		{
			m_pScoreComponent->AddPoints(m_score);
		}

	private:
		ScoreComponent* m_pScoreComponent = nullptr;
		int m_score;
	};
}