#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();

		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render();

		Scene* GetActiveScene() const { return m_scenes.back().get(); };
		void SetActiveScene(size_t sceneIndex);

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};

		Scene* m_pActiveScene{ nullptr };
	};
}
