#ifndef _PAUSE_MENU_CONTROLLER_COMPONENT_H_
#define _PAUSE_MENU_CONTROLLER_COMPONENT_H_

#include "../../../Core/Components/Component.h"

class PauseMenuControllerComponent : public Component
{
public:

	PauseMenuControllerComponent(const ComponentCreate* pCreationData, GameObject* pOwner);
	virtual ~PauseMenuControllerComponent();

	virtual void OnMessage(Message* pMessage);

private:


};

#endif
