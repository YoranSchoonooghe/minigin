#pragma once
#include "Singleton.h"
#include "SceneHierarchy.h"
#include <memory>

namespace dae
{
	class Editor final : public Singleton<Editor>
	{
	public:
		explicit Editor();
		void RenderUI();

	private:
		std::unique_ptr<SceneHierarchy> m_pSceneHierarchy;
	};
}