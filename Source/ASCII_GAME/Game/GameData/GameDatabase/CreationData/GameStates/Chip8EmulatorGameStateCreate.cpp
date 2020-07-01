#include "Chip8EmulatorGameStateCreate.h"
#include "../../../../GameStates/GameStateType.h"
#include "../../../../../Core/GameDatabase/GameDataHelpers.h"

Chip8EmulatorGameStateCreate::Chip8EmulatorGameStateCreate()
{
	m_RomFilename = "";
}

Chip8EmulatorGameStateCreate::~Chip8EmulatorGameStateCreate()
{
}

int Chip8EmulatorGameStateCreate::GetGameStateType() const 
{
	return (int)E_STATE_TYPE_CHIP_8_EMULATOR; 
}

void Chip8EmulatorGameStateCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_RomFilename, buffer);

	GameStateCreate::InitialiseFromBinary(buffer);
}