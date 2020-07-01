#ifndef _CHIP_8_EMULATOR_COMPONENT_CREATE_H_
#define _CHIP_8_EMULATOR_COMPONENT_CREATE_H_

#include "../../../../Core/GameDatabase/CreationData/ComponentCreate.h"

class Chip8EmulatorComponentCreate : public ComponentCreate
{
public:

	virtual const int GetComponentType() const;
	
	const char* filename;

	virtual void InitialiseFromBinary(char*& buffer);
	virtual Chip8EmulatorComponentCreate* Clone() const { return new Chip8EmulatorComponentCreate(*this); }
};

#endif
