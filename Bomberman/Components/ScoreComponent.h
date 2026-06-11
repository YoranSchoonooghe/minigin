#pragma once
#include "Components/Component.h"
#include <memory>
#include <Events/Subject.h>

namespace dae
{
	class EventManager;

	class ScoreComponent final : public Component, public Observer
	{
	public:
		explicit ScoreComponent(GameObject* pOwner, int startScore = 0);
		~ScoreComponent();
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;

		void AddPoints(int points);
		int GetScore() const;

		Subject* GetSubject();

	private:
		std::unique_ptr<Subject> m_onScoreChanged;
		int m_score;

		EventManager* m_pEventManager{ nullptr };
	};
}