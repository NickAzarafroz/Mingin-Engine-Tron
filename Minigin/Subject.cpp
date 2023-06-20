#include "Subject.h"
using namespace dae;

template<typename... Args>
Subject<Args...>::~Subject()
{
	for (auto& observer : m_Observers)
	{
		observer->OnSubjectDestroy();
	}
}

template<typename... Args>
void Subject<Args...>::AddObserver(Observer<Args...>* pObserver)
{
	m_Observers.push_back(pObserver);
}

template<typename... Args>
void Subject<Args...>::RemoveObserver(Observer<Args...>* pObserver)
{
	m_Observers.erase(std::remove(m_Observers.begin(), m_Observers.end(), pObserver), m_Observers.end());
}

template<typename... Args>
void Subject<Args...>::Notify(Args... args)
{
	for (auto& observer : m_Observers)
	{
		observer->HandleEvent(args...);
	}
}