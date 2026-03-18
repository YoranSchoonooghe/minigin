#pragma once
#if USE_STEAMWORKS
#include "Component.h"
#include "Events/Observer.h"

namespace dae
{
	class Subject;

	class SteamAchievementComponent final : public Component, public Observer
	{
	public:
		explicit SteamAchievementComponent(GameObject* pOwner, GameObject* pScoreOwner);
		~SteamAchievementComponent();
		SteamAchievementComponent(const SteamAchievementComponent& other) = delete;
		SteamAchievementComponent(SteamAchievementComponent&& other) = delete;
		SteamAchievementComponent& operator=(const SteamAchievementComponent& other) = delete;
		SteamAchievementComponent& operator=(SteamAchievementComponent&& other) = delete;

		void Notify(const Event& event, GameObject* pGameObject) override;

	private:
		Subject* m_pScoreComponentSubject = nullptr;
	};
}
#endif