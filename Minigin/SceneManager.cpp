#include "SceneManager.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::FixedUpdate(float fixedDeltaTime)
{
	if (!m_pActiveScene) return;

	m_pActiveScene->FixedUpdate(fixedDeltaTime);
}

void dae::SceneManager::Update(float deltaTime)
{
	if (!m_pActiveScene) return;

	m_pActiveScene->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	if (!m_pActiveScene) return;

	m_pActiveScene->Render();
}

void dae::SceneManager::SetActiveScene(size_t sceneIndex)
{
	if (sceneIndex >= 0 && sceneIndex < m_scenes.size())
	{
		m_pActiveScene = m_scenes[sceneIndex].get();
	}
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	m_pActiveScene = GetActiveScene();
	return *m_scenes.back();
}
