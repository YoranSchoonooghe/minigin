#pragma once
#include "Component.h"
#include "Events/Observer.h"

namespace dae
{
	class TextComponent;
	class Subject;

	class ScoreDisplayComponent final : public Component, public Observer
	{
	public:
		explicit ScoreDisplayComponent(GameObject* pOwner, GameObject* pScoreOwner);
		~ScoreDisplayComponent();
		ScoreDisplayComponent(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent(ScoreDisplayComponent&& other) = delete;
		ScoreDisplayComponent& operator=(const ScoreDisplayComponent& other) = delete;
		ScoreDisplayComponent& operator=(ScoreDisplayComponent&& other) = delete;

		void Update(float deltaTime) override;
		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		void UpdateDisplayText();

		TextComponent* m_pTextComponent = nullptr;
		Subject* m_pScoreComponentSubject = nullptr;
		int m_score = 0;
	};
}