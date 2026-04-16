#pragma once
#include <memory>
#include <string>
#include <vector>
#include "GameObject.h"
#include "CollisionSystem.h"

namespace dae
{
	class Scene final
	{
	public:
		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();

		void FixedUpdate(float fixedDeltaTime);
		void Update(float deltaTime);
		void Render() const;
		void RenderUI();

		void CleanupDestroyedComponents();

		CollisionSystem* GetCollisionSystem() const { return m_pCollisionSystem.get(); };
		std::vector<GameObject*> GetGameObjects() const;

		void SetCamera(GameObject* pCamera) { m_pCamera = pCamera; };
		GameObject* GetActiveCamera() const { return m_pCamera; };

	private:
		friend class SceneManager;
		explicit Scene();

		std::unique_ptr<CollisionSystem> m_pCollisionSystem;
		std::vector < std::unique_ptr<GameObject>> m_pGameObjects{};

		GameObject* m_pCamera{ nullptr };
	};

}
