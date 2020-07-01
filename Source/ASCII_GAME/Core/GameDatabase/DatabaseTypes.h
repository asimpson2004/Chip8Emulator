#ifndef _DATA_ITEM_H_
#define _DATA_ITEM_H_

#include <vector>
#include "../Utils/Utils.h"

namespace GDb
{
    
class C_DataItem
{
public:
	C_DataItem();
	virtual ~C_DataItem();

	virtual void InitialiseFromBinary(char*& buffer) = 0;
};

class C_VDataItem : public C_DataItem //for use with C_Pointer data type
{
public:
	C_VDataItem();
	virtual ~C_VDataItem();

	virtual C_VDataItem* Clone() const = 0; //Virtual copy pattern
};

template <class T>
class C_Array : public std::vector<T>
{

};
    
extern void *GetDataFromID(const unsigned int dataId);

template <class T>
class C_Ref
{
public:
    
    T& operator*(){return *GetItem();}    // returns reference to item
    operator const T*() const {return GetItem();} // conversion operator
    
    const T * GetItem(void) const
    {        
        return (T*)GetDataFromID(m_ItemId);
    }
    unsigned int     m_ItemId;
};

template <class T>
class C_Pointer //must only use with classes that derive from C_VDataItem only
{
public:

	C_Pointer() : m_pData(nullptr) {}
	C_Pointer(const C_Pointer& pointer) // copy constructor for deep copy to enable use with vectors
	:m_Hashcode(pointer.m_Hashcode)
	,m_pData(pointer.m_pData ? pointer.m_pData->Clone() : nullptr) //we dont know the type at this point so use virtual copy pattern
	{
	}

	~C_Pointer() { SAFE_DELETE_PTR(m_pData); }

	T& operator*() { return *GetItem(); }    // returns reference to item
	operator const T*() const { return GetItem(); } // conversion operator

	const T * GetItem(void) const
	{
		return (T*)m_pData;
	}

	unsigned int m_Hashcode;

	C_VDataItem* m_pData;
};

} // namespace GDb
#endif //_GAME_DATA_BASE_H_
