#include "Chip8EmulatorComponentCreate.h"
#include "../../../../Core/GameDatabase/GameDataHelpers.h"
#include "../../../Components/GameComponentType.h"

const int Chip8EmulatorComponentCreate::GetComponentType() const 
{ 
	return (int)E_GameComponentType::E_GAME_COMPONENT_TYPE_CHIP_8; 
}

void Chip8EmulatorComponentCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&filename, buffer);
	ComponentCreate::InitialiseFromBinary(buffer);
}
