#pragma once
#include <vector>
#include "Observer.h"
namespace dae
{
	template<typename... Args>
	class Subject final
	{
	public:
		~Subject()
		{
			for(auto& observer : m_Observers)
			{
				observer->OnSubjectDestroy();
			}
		}
		void AddObserver(Observer<Args...>* pObserver)
		{
			m_Observers.push_back(pObserver);
		}
		void RemoveObserver(Observer<Args...>* pObserver)
		{
			m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), pObserver), m_Observers.end());
		}
		void Notify(Args... args)
		{
			for (auto& observer : m_Observers)
			{
				observer->HandleEvent(args...);
			}
		}

	private:
		std::vector<Observer<Args...>*> m_Observers;
	};
}


