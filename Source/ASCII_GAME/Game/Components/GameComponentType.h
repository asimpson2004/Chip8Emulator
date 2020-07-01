#ifndef _GAME_COMPONENT_TYPE_H_
#define _GAME_COMPONENT_TYPE_H_

#include "../../Core/Components/ComponentType.h"

enum class E_GameComponentType
{
	E_GAME_COMPONENT_TYPE_CHIP_8 = (int)E_Component_Type::E_COMPONENT_TYPE_MAX,
	E_GAME_COMPONENT_TYPE_CHIP_8_GAME_STATE_LAUNCHER,
	E_GAME_COMPONENT_TYPE_PAUSE_MENU_CONTROLLER,
};

#endif
