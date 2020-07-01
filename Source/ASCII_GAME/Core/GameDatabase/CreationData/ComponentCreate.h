#ifndef _COMPONENT_CREATE_H_
#define _COMPONENT_CREATE_H_

#include "../DatabaseTypes.h"

class ComponentCreate : public GDb::C_VDataItem
{
public:
	ComponentCreate();
	virtual ~ComponentCreate() {}
	virtual const int GetComponentType() const { return -1;  };

	int m_ComponentId;

	virtual void InitialiseFromBinary(char*& buffer);
	virtual ComponentCreate* Clone() const { return new ComponentCreate(*this); }
};

#endif
