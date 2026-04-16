#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Editor.h"
#include "SceneManager.h"
#include <algorithm>


dae::BoxColliderComponent::BoxColliderComponent(GameObject* pOwner, float width, float height, const glm::vec2& offset, bool isTrigger, float pushThreshold, float pushValue)
	: Component{ pOwner }
	, m_width{ width }, m_height{ height }, m_offset{ offset }, m_isTrigger{ isTrigger }
	, m_pushThreshold{ pushThreshold }, m_pushValue{ pushValue }
{
	m_pTriggerSubject = std::make_unique<Subject>();

	SceneManager::GetInstance().GetActiveScene()->GetCollisionSystem()->Register(this);
}

dae::BoxColliderComponent::~BoxColliderComponent()
{
	auto pActiveScene = SceneManager::GetInstance().GetActiveScene();
	if (pActiveScene)
	{
		auto pCollisionSystem = pActiveScene->GetCollisionSystem();
		if (pCollisionSystem)
		{
			pCollisionSystem->Unregister(this);
		}
	}

	m_pTriggerSubject->NotifyObservers(Event(make_sdbm_hash("OnSubjectDestroyed")), GetOwner());
}

void dae::BoxColliderComponent::Render() const
{
	if (!Editor::GetInstance().IsDrawCollisionShapesEnabled()) return;

	const auto& worldPosition = GetOwner()->GetWorldPosition();
	const auto& cameraPosition = SceneManager::GetInstance().GetActiveScene()->GetActiveCamera()->GetWorldPosition();

	SDL_Color debugColor = { 0, 255, 255, 150 };

	Renderer::GetInstance().RenderRect(
		worldPosition.x + m_offset.x - cameraPosition.x,
		worldPosition.y + m_offset.y - cameraPosition.y,
		m_width,
		m_height,
		debugColor
	);
}

dae::Rect dae::BoxColliderComponent::GetCollider() const
{
	const auto& worldPosition = GetOwner()->GetWorldPosition();

	Rect collider{};

	collider.left = worldPosition.x + m_offset.x;
	collider.top = worldPosition.y + m_offset.y;
	collider.width = m_width;
	collider.height = m_height;

	return collider;
}

void dae::BoxColliderComponent::AddOverlappingGameObject(GameObject* pGameObject)
{
	if (std::ranges::find(m_pOverlappingGameObjects, pGameObject) != m_pOverlappingGameObjects.end()) return;

	m_pOverlappingGameObjects.push_back(pGameObject);

	m_pTriggerSubject->NotifyObservers(Event(make_sdbm_hash("OnTriggerEnter")), pGameObject);
}

void dae::BoxColliderComponent::RemoveOverlappingGameObject(GameObject* pGameObject)
{
	std::erase(m_pOverlappingGameObjects, pGameObject);

	m_pTriggerSubject->NotifyObservers(Event(make_sdbm_hash("OnTriggerExit")), pGameObject);
}
