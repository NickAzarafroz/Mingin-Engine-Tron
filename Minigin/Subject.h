#pragma once
#include <vector>
#include "Observer.h"

namespace dae
{
	template<typename... Args>
	class Subject final
	{
	public:
		Subject() = default;
		~Subject() 
		{
			for (auto& observer : m_Observers)
			{
				observer->OnSubjectDestroy();
			}
		}

		Subject(const Subject& other) = delete;
		Subject(Subject&& other) = delete;
		Subject& operator=(const Subject& other) = delete;
		Subject& operator=(Subject&& other) = delete;

		void AddObserver(Observer<Args...>* pObserver)
		{
			m_Observers.emplace_back(pObserver);
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

