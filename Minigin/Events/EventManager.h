#pragma once
#include "Singleton.h"
#include "Observer.h"
#include <vector>

namespace dae
{
	class EventManager final : public Singleton<EventManager>
	{
	public:
		~EventManager()
		{
			SendEvent(Event(make_sdbm_hash("OnEventManagerDestroyed")), nullptr);
		}

		void AddObserver(Observer* pObserver)
		{
			m_pObservers.push_back(pObserver);
		}

		void RemoveObserver(Observer* pObserver)
		{
			std::erase(m_pObservers, pObserver);
		}

		void SendEvent(const Event& event, GameObject* pGameObject)
		{
			for (auto* pObserver : m_pObservers)
			{
				pObserver->Notify(event, pGameObject);
			}
		}

	private:
		friend class Singleton<EventManager>;
		EventManager() = default;

		std::vector<Observer*> m_pObservers;

	};
}