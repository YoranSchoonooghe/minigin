#include "BoxColliderComponent.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Editor.h"
#include "SceneManager.h"
#include <algorithm>
#include "imgui.h"


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

void dae::BoxColliderComponent::RenderUI()
{
	if (ImGui::CollapsingHeader("Box Collider", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::PushItemWidth(80);

		ImGui::Text("Width"); ImGui::SameLine();
		ImGui::DragFloat("##Width", &m_width, 1.0f, 0.0f, 0.0f, "%.1f");
		ImGui::SameLine();
		ImGui::Text("Height"); ImGui::SameLine();
		ImGui::DragFloat("##Height", &m_height, 1.0f, 0.0f, 0.0f, "%.1f");


		ImGui::Text("Offset"); ImGui::SameLine();

		ImGui::Text("X"); ImGui::SameLine();
		ImGui::DragFloat("##OffsetX", &m_offset.x, 1.0f, 0.0f, 0.0f, "%.1f");
		ImGui::SameLine();
		ImGui::Text("Y"); ImGui::SameLine();
		ImGui::DragFloat("##OffsetY", &m_offset.y, 1.0f, 0.0f, 0.0f, "%.1f");

		ImGui::PopItemWidth();

		ImGui::Separator();

		ImGui::Text("Trigger"); ImGui::SameLine();
		ImGui::Checkbox("##Trigger", &m_isTrigger);

		ImGui::Separator();

		ImGui::PushItemWidth(80);

		ImGui::Text("Push Threshold"); ImGui::SameLine();
		ImGui::DragFloat("##PushThreshold", &m_pushThreshold, 1.0f, 0.0f, 0.0f, "%.1f");

		ImGui::Text("Push Value"); ImGui::SameLine();
		ImGui::DragFloat("##PushValue", &m_pushValue, 1.0f, 0.0f, 0.0f, "%.1f");

		ImGui::PopItemWidth();
	}
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
