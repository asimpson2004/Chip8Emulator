#include "PauseMenuControllerComponentCreate.h"
#include "../../../../Components/GameComponentType.h"

const int PauseMenuComponentControllerComponentCreate::GetComponentType() const
{
	return (int)E_GameComponentType::E_GAME_COMPONENT_TYPE_PAUSE_MENU_CONTROLLER;
}

void PauseMenuComponentControllerComponentCreate::InitialiseFromBinary(char*& buffer)
{
	ComponentCreate::InitialiseFromBinary(buffer);
}
