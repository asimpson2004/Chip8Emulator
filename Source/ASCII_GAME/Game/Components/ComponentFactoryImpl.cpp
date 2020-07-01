#include "ComponentFactoryImpl.h"

#include "GameComponentType.h"
#include "../../Core/GameDatabase/CreationData/ComponentCreate.h"

#include "../Components/Chip8EmulatorComponent.h"
#include "../Components/UI/Chip8GameStateLauncherComponent.h"
#include "../Components/UI/PauseMenuControllerComponent.h"

Component* ComponentFactoryImpl::GetComponent(const ComponentCreate* pCreationData, GameObject* pOwnerGameObject)
{
	if (pCreationData == nullptr)
		return nullptr;

	switch ((E_GameComponentType)pCreationData->GetComponentType())
	{
		case E_GameComponentType::E_GAME_COMPONENT_TYPE_CHIP_8:
		{
			return new Chip8EmulatorComponent(pCreationData, pOwnerGameObject);
		}
		break;
		case E_GameComponentType::E_GAME_COMPONENT_TYPE_CHIP_8_GAME_STATE_LAUNCHER:
		{
			return new Chip8GameStateLauncherComponent(pCreationData, pOwnerGameObject);
		}
		break;
		case E_GameComponentType::E_GAME_COMPONENT_TYPE_PAUSE_MENU_CONTROLLER:
		{
			return new PauseMenuControllerComponent(pCreationData, pOwnerGameObject);
		}
		break;
	}

	return ComponentFactory::GetComponent(pCreationData, pOwnerGameObject);
}
