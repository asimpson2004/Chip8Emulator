#ifndef _CHIP_8_GAME_STATE_LAUNCHER_COMPONENT_CREATE_H_
#define _CHIP_8_GAME_STATE_LAUNCHER_COMPONENT_CREATE_H_

#include "../../../../../Core/GameDatabase/CreationData/ComponentCreate.h"

class Chip8GameStateLauncherComponentCreate : public ComponentCreate
{
public:

	virtual const int GetComponentType() const;

	virtual void InitialiseFromBinary(char*& buffer);
	virtual Chip8GameStateLauncherComponentCreate* Clone() const { return new Chip8GameStateLauncherComponentCreate(*this); }
};

#endif
