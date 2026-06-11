#pragma once
#include "Singleton.h"
#include <memory>
#include "SceneHierarchy.h"
#include "Properties.h"

namespace dae
{
	class GameObject;

	class Editor final : public Singleton<Editor>
	{
	public:
		void Init();
		void RenderUI();

		void SetSelectedGameObject(GameObject* pGameObject) { m_pSelectedGameObject = pGameObject; };
		GameObject* GetSelectedGameObject() const { return m_pSelectedGameObject; };

		bool IsDrawCollisionShapesEnabled() const { return m_drawCollisionShapes; };
		void SetDrawCollisionShapes(bool enabled) { m_drawCollisionShapes = enabled; };

	private:
		std::unique_ptr<SceneHierarchy> m_pSceneHierarchy;
		std::unique_ptr<Properties> m_pProperties;

		GameObject* m_pSelectedGameObject = nullptr;

		bool m_drawCollisionShapes = false;
	};
}