// CPUBurning.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

 
template<typename V>
class IHookInterface
{
public:
	virtual bool operator()(V v)= 0;
};

template<typename C, typename V = C::value_type>
class CContainerPerformance
{
public:
	CContainerPerformance(C* pContainer):m_pContainer(pContainer){}

	size_t RemoveFromFront(IHookInterface<V>& F)
	{
		while(!m_pContainer->empty())
		{
			V v = *m_pContainer->begin();
			m_pContainer->erase(m_pContainer->begin());
			if(F(v))
			{
				break;
			}
		}
		return m_pContainer->size();
	}

private:
	std::auto_ptr<C> m_pContainer;
};


template<typename V>
class CDefaultHook: public IHookInterface<V>
{
public:
	bool operator()(V v)
	{
		//std::cout << v << std::endl;
		return false;
	}
};

namespace
{
	HANDLE g_evtStop = NULL;
};

template<typename C>
unsigned _stdcall RemoveThread(void* pContainer)
{
	CContainerPerformance<C>* pC = static_cast<CContainerPerformance<C>*>(pContainer);
	pC->RemoveFromFront((IHookInterface<int>&)CDefaultHook<int>());
	::WaitForSingleObject(g_evtStop, INFINITE);
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	const static size_t COUNT = 100 * 10000;

	srand( (unsigned)time( NULL ));

	std::vector<int>* pIntVec = new std::vector<int>(COUNT);
	for(int& i: *pIntVec){i = rand();};

	std::list<int>* pIntList = new std::list<int>(COUNT);
	for(int& i: *pIntList){i = rand();}

	std::deque<int>* pIntDeque = new std::deque<int>(COUNT);
	for(int& i: *pIntDeque){i = rand();}


	CContainerPerformance<std::vector<int>> vec(pIntVec);
	CContainerPerformance<std::list<int>> lst(pIntList);
	CContainerPerformance<std::deque<int>> deq(pIntDeque);

	typedef unsigned (_stdcall *PTR)(void*);

	g_evtStop = ::CreateEvent(NULL, TRUE, FALSE, NULL);

	HANDLE threadArray[] = {
		(HANDLE)::_beginthreadex(NULL,0,(PTR)RemoveThread<std::vector<int>>,&vec,0,NULL),
		(HANDLE)::_beginthreadex(NULL,0,(PTR)RemoveThread<std::list<int>>,&lst,0,NULL),
		(HANDLE)::_beginthreadex(NULL,0,(PTR)RemoveThread<std::deque<int>>,&deq,0,NULL),
	};

	system("pause");

	::SetEvent(g_evtStop);

	::WaitForMultipleObjects(_countof(threadArray), threadArray, TRUE, INFINITE);

	std::for_each(threadArray, threadArray + _countof(threadArray), std::ptr_fun(::CloseHandle));
	CloseHandle(g_evtStop);
	return 0;
}

