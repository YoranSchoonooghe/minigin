#include <algorithm>
#include "Scene.h"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_pGameObjects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	m_pGameObjects.erase(
		std::remove_if(
			m_pGameObjects.begin(),
			m_pGameObjects.end(),
			[&object](const auto& ptr) { return ptr.get() == &object; }
		),
		m_pGameObjects.end()
	);
}

void Scene::RemoveAll()
{
	m_pGameObjects.clear();
}

void dae::Scene::FixedUpdate(float fixedDeltaTime)
{
	for (auto& object : m_pGameObjects)
	{
		object->FixedUpdate(fixedDeltaTime);
	}
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_pGameObjects)
	{
		object->Update(deltaTime);
	}

	CleanupDestroyedComponents();
}

void Scene::Render() const
{
	for (const auto& object : m_pGameObjects)
	{
		object->Render();
	}
}

void dae::Scene::CleanupDestroyedComponents()
{
	m_pGameObjects.erase(std::remove_if(m_pGameObjects.begin(), m_pGameObjects.end(),
		[](const std::unique_ptr<GameObject>& pGameObject)
		{
			return pGameObject->IsDestroyed();
		}),
		m_pGameObjects.end()
	);
}

