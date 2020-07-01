#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "FactoryHelpers.h"
#include <map>

template<class type> class Factory
{
public:
	Factory();
	~Factory();

	void AddClass(int hashcode, ConstructorFunctionPointer* ptr);
	bool IsClassInFactory(int hashcode);

	type* ConstructClass(int hashcode);

private:
	std::map<int, ConstructorFunctionPointer*> m_ConstructorMap;
};

template <class type>Factory<type>::Factory()
{
}

template <class type>Factory<type>::~Factory()
{
}

template <class type> void  Factory<type>::AddClass(int hashcode,  ConstructorFunctionPointer* ptr)
{
	m_ConstructorMap[hashcode] = ptr;
}

template <class type> bool Factory<type>::IsClassInFactory(int hashcode)
{
	return m_ConstructorMap.count(hashcode) == 0 ? false : true;
}

template <class type> type* Factory<type>::ConstructClass(int hashcode)
{
	ConstructorFunctionPointer *pConstructor =  m_ConstructorMap[hashcode];
	if(pConstructor)
		return (type*)pConstructor();
	else
		return nullptr;
}

#endif //_FACTORY_H_
