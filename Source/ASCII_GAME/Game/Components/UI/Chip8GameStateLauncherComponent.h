#ifndef _CHIP_8_GAME_STATE_LAUNCHER_COMPONENT_H_
#define _CHIP_8_GAME_STATE_LAUNCHER_COMPONENT_H_

#include "../../../Core/Components/Component.h"

class Chip8GameStateLauncherComponent : public Component
{
public:

	Chip8GameStateLauncherComponent(const ComponentCreate* pCreationData, GameObject* pOwner);
	virtual ~Chip8GameStateLauncherComponent();

	virtual void OnMessage(Message* pMessage);

private:


};

#endif
