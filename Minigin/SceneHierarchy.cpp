#include "SceneHierarchy.h"
#include "SceneManager.h"
#include "GameObject.h"
#include <imgui.h>

dae::SceneHierarchy::SceneHierarchy()
{
}

void dae::SceneHierarchy::RenderUI()
{
	ImGui::Begin("Scene Hierarchy");

    auto activeScene = SceneManager::GetInstance().GetActiveScene();
    auto gameObjects = activeScene->GetGameObjects();

    for (auto& gameObject : gameObjects) {
        if (!gameObject->GetParent())
        {
            DrawGameObjectNode(gameObject);
        }
    }

	ImGui::End();
}

void dae::SceneHierarchy::DrawGameObjectNode(GameObject* pGameObject)
{
    ImGuiTreeNodeFlags flags{};

    if (m_pSelectedGameObject == pGameObject)
    {
        flags = ImGuiTreeNodeFlags_Selected;
    }

    if (pGameObject->GetChildCount() == 0)
    {
        flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
    }

    bool opened = ImGui::TreeNodeEx((void*)pGameObject, flags, "%s", pGameObject->GetName().c_str());

    if (ImGui::IsItemClicked())
    {
        m_pSelectedGameObject = pGameObject;
    }

    if (opened && !(flags & ImGuiTreeNodeFlags_Leaf))
    {
        for (int i = 0; i < pGameObject->GetChildCount(); ++i)
        {
            DrawGameObjectNode(pGameObject->GetChildAt(i));
        }

        ImGui::TreePop();
    }
}
