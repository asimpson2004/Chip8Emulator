#ifndef _PAK_LIST_H_
#define _PAK_LIST_H_

#include "DatabaseTypes.h"

namespace GDb
{

class C_PaksList : public C_DataItem
{
public:

	C_PaksList();
	virtual ~C_PaksList();

	virtual void InitialiseFromBinary(char*& buffer);

	C_Array<const char*> m_PakFileNames;
};

}//namespace GDb

#endif //_PACK_LIST_H_
