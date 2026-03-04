#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	struct transform
	{
		float matrix[16] = {
			1,0,0,0,
			0,1,0,0,
			0,0,1,0,
			0,0,0,1
		};
	};

	class GameObjectBase
	{
	public:
		transform local{};
		int id{};
	};

	class GameObjectAlt
	{
	public:
		transform* local{};
		int id{};
	};

	class ThrashCacheComponent final : public Component
	{
	public:
		explicit ThrashCacheComponent(GameObject* pOwner);
		~ThrashCacheComponent() = default;
		ThrashCacheComponent(const ThrashCacheComponent& other) = delete;
		ThrashCacheComponent(ThrashCacheComponent&& other) = delete;
		ThrashCacheComponent& operator=(const ThrashCacheComponent& other) = delete;
		ThrashCacheComponent& operator=(ThrashCacheComponent&& other) = delete;

		void RenderUI() override;

	private:
		void RenderExercise1();
		void RenderExercise2();
		void RenderExercise2Base();
		void RenderExercise2Alt();
		void RenderExercise2Combined();

		std::vector<float> ThrashCache(int samples) const;
		std::vector<float> ThrashCacheGameObject(int samples) const;
		std::vector<float> ThrashCacheGameObjectAlt(int samples) const;

		int m_samplesExercise1 = 10;
		int m_samplesExercise2 = 100;
		std::vector<float> m_plotDataExercise1{};
		std::vector<float> m_plotDataExercise2{};
		std::vector<float> m_plotDataExercise2Alt{};

		const char* STEP_LABELS[11] = { "1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024" };
		const double STEP_INDICES[11] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
		const char* STEP_LABELS_HALF[6] = { "1", "4", "16", "64", "256", "1024" };
		const double STEP_INDICES_HALF[6] = { 0, 2, 4, 6, 8, 10 };
	};
}