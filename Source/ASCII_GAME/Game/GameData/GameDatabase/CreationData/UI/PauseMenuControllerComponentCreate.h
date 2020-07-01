#ifndef _PAUSE_MENU_CONTROLLER_COMPONENT_CREATE_H_
#define _PAUSE_MENU_CONTROLLER_COMPONENT_CREATE_H_

#include "../../../../../Core/GameDatabase/CreationData/ComponentCreate.h"


class PauseMenuComponentControllerComponentCreate : public ComponentCreate
{
public:

	virtual const int GetComponentType() const;

	virtual void InitialiseFromBinary(char*& buffer);
	virtual PauseMenuComponentControllerComponentCreate* Clone() const { return new PauseMenuComponentControllerComponentCreate(*this); }
};

#endif
