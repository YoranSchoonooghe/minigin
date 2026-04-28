#pragma once
#include "Components/Component.h"
#include "Events/Observer.h"
#include <string>

namespace dae
{
	class TextComponent;
	class Subject;

	class ScoreDisplayComponent final : public Component, public Observer
	{
	public:
		explicit ScoreDisplayComponent(GameObject* pOwner, GameObject* pScoreOwner, const std::string& label = "Score:");
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
		std::string m_label;
	};
}