#include "Chip8GameStateLauncherComponentCreate.h"
#include "../../../../Components/GameComponentType.h"

const int Chip8GameStateLauncherComponentCreate::GetComponentType() const
{
	return (int)E_GameComponentType::E_GAME_COMPONENT_TYPE_CHIP_8_GAME_STATE_LAUNCHER;
}

void Chip8GameStateLauncherComponentCreate::InitialiseFromBinary(char*& buffer)
{
	ComponentCreate::InitialiseFromBinary(buffer);
}
