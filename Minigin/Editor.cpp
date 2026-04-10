#include "Editor.h"

dae::Editor::Editor()
{
	m_pSceneHierarchy = std::make_unique<SceneHierarchy>();
	m_pProperties = std::make_unique<Properties>();
}

void dae::Editor::RenderUI()
{
	m_pSceneHierarchy->RenderUI();
	m_pProperties->RenderUI();
}
