#ifndef _CHIP_8_EMULATOR_GAME_STATE_CREATE_H_
#define _CHIP_8_EMULATOR_GAME_STATE_CREATE_H_

#include "../../../../../Core/GameDatabase/CreationData/GameStateCreate.h"

class Chip8EmulatorGameStateCreate : public GameStateCreate
{
public:

	Chip8EmulatorGameStateCreate();
	virtual ~Chip8EmulatorGameStateCreate();

	virtual int GetGameStateType() const;

	const char* m_RomFilename;

	virtual void InitialiseFromBinary(char*& buffer);
};

#endif
