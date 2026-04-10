#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;

	class SceneHierarchy final
	{
	public:
		explicit SceneHierarchy();
		~SceneHierarchy() = default;
		SceneHierarchy(const SceneHierarchy& other) = delete;
		SceneHierarchy(SceneHierarchy&& other) = delete;
		SceneHierarchy& operator=(const SceneHierarchy& other) = delete;
		SceneHierarchy& operator=(SceneHierarchy&& other) = delete;

		void RenderUI();

	private:
		void DrawGameObjectNode(GameObject* gameObject);

		GameObject* m_pSelectedGameObject = nullptr;
	};
}