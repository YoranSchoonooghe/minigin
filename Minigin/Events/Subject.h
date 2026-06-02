#pragma once
#include <vector>
#include "Observer.h"
#include "Event.h"

namespace dae
{
	class Subject
	{
	public:
		void AddObserver(Observer* pObserver)
		{
			m_pObservers.push_back(pObserver);
		}

		void RemoveObserver(Observer* pObserver)
		{
			std::erase(m_pObservers, pObserver);
		}

		void NotifyObservers(const Event& event, GameObject* pGameObject)
		{
			for (auto* pObserver : m_pObservers)
			{
				pObserver->Notify(event, pGameObject);
			}
		}

	private:
		std::vector<Observer*> m_pObservers;
	};
}