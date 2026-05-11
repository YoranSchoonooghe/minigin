#pragma once
#include "Singleton.h"

namespace dae
{
	class GameManager final : public Singleton<GameManager>
	{
	public:
		void ExitStage();

		int GetStageNumber() const { return m_stageNumber; }

	private:
		int m_stageNumber{ 1 };
		//int m_lives{ 3 };
		//int m_score{ 0 };

	};
}