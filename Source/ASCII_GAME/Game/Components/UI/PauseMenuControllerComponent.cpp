#include "PauseMenuControllerComponent.h"
#include "../../../Core/Messages/Message.h"
#include "../../../Core/Messages/MessageType.h"
#include "../../../Core/Messages/MenuItemSelectedMessage.h"

#include "../../../Core/GameState/GameStateManager.h"

PauseMenuControllerComponent::PauseMenuControllerComponent(const ComponentCreate* pCreationData, GameObject* pOwner)
	:Component(pCreationData, pOwner)
{
}

PauseMenuControllerComponent::~PauseMenuControllerComponent()
{
}

void PauseMenuControllerComponent::OnMessage(Message* pMessage)
{
	if (pMessage == nullptr)
		return;

	switch (pMessage->GetMessageType())
	{
		case (int)E_MESSAGE_TYPE::MENU_ITEM_SELECTED:
		{
			const MenuItemSelectedMessage* pMenuItemSelectedMessage = dynamic_cast<const MenuItemSelectedMessage*>(pMessage);
			if (pMenuItemSelectedMessage)
			{
				if (pMenuItemSelectedMessage->m_MenuItem.compare("Resume") == 0)
				{
					GameStateManager::Instance()->PopGameState();
				}
				else if (pMenuItemSelectedMessage->m_MenuItem.compare("Quit") == 0)
				{
					GameStateManager::Instance()->PopGameState();
					GameStateManager::Instance()->PopGameState();
				}
			}
		}
		break;
		default:
		{
		}
		break;
	}
}
