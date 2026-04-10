#include "Properties.h"
#include <imgui.h>
#include "Editor.h"
#include "GameObject.h"

dae::Properties::Properties()
{
}

void dae::Properties::RenderUI()
{
    ImGui::Begin("Properties");

    if (ImGui::BeginTabBar("PropertiesTabs"))
    {
        if (ImGui::BeginTabItem("GameObject"))
        {
            //ImGui::Text("Object view content");
            RenderTransformProperties();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Scene"))
        {
            ImGui::Text("Scene view content");
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Global"))
        {
            RenderGlobalProperties();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}

void dae::Properties::RenderTransformProperties()
{
    auto pSelectedGameObject{ Editor::GetInstance().GetSelectedGameObject() };
    if (!pSelectedGameObject) return;

    if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
    {
        auto position = pSelectedGameObject->GetLocalPosition();
        float pos[3] = { position.x, position.y, position.z };

        ImGui::Text("Position");
        ImGui::SameLine();

        ImGui::PushItemWidth(80);

        ImGui::Text("X"); ImGui::SameLine();
        if (ImGui::DragFloat("##X", &pos[0], 1.0f, 0.0f, 0.0f, "%.1f"))
            pSelectedGameObject->SetLocalPosition({ pos[0], pos[1], pos[2] });

        ImGui::SameLine();
        ImGui::Text("Y"); ImGui::SameLine();
        if (ImGui::DragFloat("##Y", &pos[1], 1.0f, 0.0f, 0.0f, "%.1f"))
            pSelectedGameObject->SetLocalPosition({ pos[0], pos[1], pos[2] });

        ImGui::SameLine();
        ImGui::Text("Z"); ImGui::SameLine();
        if (ImGui::DragFloat("##Z", &pos[2], 1.0f, 0.0f, 0.0f, "%.1f"))
            pSelectedGameObject->SetLocalPosition({ pos[0], pos[1], pos[2] });

        ImGui::PopItemWidth();
    }
}

void dae::Properties::RenderGlobalProperties()
{
    bool drawCollisioinShapes = Editor::GetInstance().IsDrawCollisionShapesEnabled();

    if (ImGui::Checkbox("Draw Collision Shapes", &drawCollisioinShapes))
        Editor::GetInstance().SetDrawCollisionShapes(drawCollisioinShapes);
}
