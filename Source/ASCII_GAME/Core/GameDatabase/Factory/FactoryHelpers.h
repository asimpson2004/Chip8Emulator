#ifndef _FACTORY_HELPERS_H_
#define _FACTORY_HELPERS_H_

template<class type> void* Constructor()
{
	return reinterpret_cast<void*>(new type());
}

typedef void* ConstructorFunctionPointer();
typedef void DestructorFunctionPointer(void*);

#endif //_FACTORY_HELPERS_H_
