#include "Editor.h"

dae::Editor::Editor()
{
	m_pSceneHierarchy = std::make_unique<SceneHierarchy>();
}

void dae::Editor::RenderUI()
{
	m_pSceneHierarchy->RenderUI();
}
