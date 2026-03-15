#include "ScoreComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* pOwner, int startScore)
	: Component{ pOwner }
	, m_score{ startScore }
{
}

void dae::ScoreComponent::AddPoints(int points)
{
	m_score += points;

	//dispatch event that score changed
}
