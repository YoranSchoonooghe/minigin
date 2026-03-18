#if USE_STEAMWORKS
#include "SteamAchievementComponent.h"
#include "ScoreComponent.h"
#include "SpacewarAchievements.h"

dae::SteamAchievementComponent::SteamAchievementComponent(GameObject* pOwner, GameObject* pScoreOwner)
	: Component{ pOwner }
{
	ScoreComponent* pScoreComponent = pScoreOwner->GetComponent<ScoreComponent>();
	m_pScoreComponentSubject = pScoreComponent->OnScoreChanged();
	m_pScoreComponentSubject->AddObserver(this);
}

dae::SteamAchievementComponent::~SteamAchievementComponent()
{
	if (m_pScoreComponentSubject)
	{
		m_pScoreComponentSubject->RemoveObserver(this);
	}
}

void dae::SteamAchievementComponent::Notify(const Event& event, GameObject* pGameObject)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnScoreChanged"):
	{
		const int SCORE = pGameObject->GetComponent<ScoreComponent>()->GetScore();
		const int SCORE_THRESHOLD = 500;
		if (SCORE >= SCORE_THRESHOLD && g_SteamAchievements)
		{
			g_SteamAchievements->SetAchievement("ACH_WIN_ONE_GAME");
		}
		break;
	}
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pScoreComponentSubject = nullptr;
		break;
	}
}
#endif