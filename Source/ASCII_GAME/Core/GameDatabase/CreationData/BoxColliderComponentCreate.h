#ifndef _BOX_COLLIDER_COMPONENT_CREATE_H_
#define _BOX_COLLIDER_COMPONENT_CREATE_H_

#include "ComponentCreate.h"

class BoxColliderComponentCreate : public ComponentCreate
{
public:

	virtual void InitialiseFromBinary(char*& buffer) { ComponentCreate::InitialiseFromBinary(buffer); }
	virtual BoxColliderComponentCreate* Clone() const { return new BoxColliderComponentCreate(*this); }
};

#endif
