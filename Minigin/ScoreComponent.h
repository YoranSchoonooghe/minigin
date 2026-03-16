#pragma once
#include "Component.h"
#include <memory>
#include <Events/Subject.h>

namespace dae
{
	class ScoreComponent final : public Component
	{
	public:
		explicit ScoreComponent(GameObject* pOwner, int startScore = 0);
		~ScoreComponent();
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void AddPoints(int points);
		int GetScore() const;

		Subject* OnScoreChanged();

	private:
		std::unique_ptr<Subject> m_onScoreChanged;
		int m_score;
	};
}