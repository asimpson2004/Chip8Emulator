#include "Chip8GameStateLauncherComponent.h"
#include "../../../Core/Messages/Message.h"
#include "../../../Core/Messages/MessageType.h"
#include "../../../Core/Messages/MenuItemSelectedMessage.h"

#include "../../GameData/GameDatabase/CreationData/GameStates/Chip8EmulatorGameStateCreate.h"

Chip8GameStateLauncherComponent::Chip8GameStateLauncherComponent(const ComponentCreate* pCreationData, GameObject* pOwner)
:Component(pCreationData, pOwner)
{
}

Chip8GameStateLauncherComponent::~Chip8GameStateLauncherComponent()
{
}

void Chip8GameStateLauncherComponent::OnMessage(Message* pMessage)
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
				Chip8EmulatorGameStateCreate chip8EmulatorGameStateCreate;
				chip8EmulatorGameStateCreate.m_RomFilename = pMenuItemSelectedMessage->m_MenuItem.c_str();

				GameStateManager::Instance()->PushGameState(&chip8EmulatorGameStateCreate);
			}
		}
		break;
		default:
		{
		}
		break;
	}
}
