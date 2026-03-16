#pragma once
#include "GameObject.h"
#include "Event.h"

namespace dae
{
	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const Event& event, GameObject* pGameObject) = 0;
	};
}