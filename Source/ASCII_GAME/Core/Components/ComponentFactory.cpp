#include "ComponentFactory.h"
#include "Component.h"
#include "ComponentType.h"

#include "Graphics/SpriteComponent.h"
#include "Graphics/AnimatorComponent.h"

#include "../GameDatabase/CreationData/ComponentCreate.h"
#include "../GameDatabase/CreationData/SpriteComponentCreate.h"
#include "../GameDatabase/CreationData/AnimatorComponentCreate.h"
#include "../GameDatabase/CreationData/BoxColliderComponentCreate.h"

//UIComponents
#include "UI/ListMenuComponent.h"
#include "UI/FileListMenuComponent.h"
#include "UI/TextComponent.h"

Component* ComponentFactory::GetComponent(const ComponentCreate* pCreationData, GameObject* pOwnerGameObject)
{
	if (pCreationData == nullptr)
		return nullptr;

	switch ((E_Component_Type)pCreationData->GetComponentType())
	{
		case E_Component_Type::E_COMPONENT_TYPE_SPRITE:
		{
			return new SpriteComponent(dynamic_cast<const SpriteComponentCreate*>(pCreationData), pOwnerGameObject);
		}
		break;
		case E_Component_Type::E_COMPONENT_TYPE_ANIMATOR:
		{
			return new AnimatorComponent(dynamic_cast<const AnimatorComponentCreate*>(pCreationData), pOwnerGameObject);
		}
		break;
		case E_Component_Type::E_COMPONENT_TYPE_UI_LIST_MENU:
		{
			return new ListMenuComponent(pCreationData, pOwnerGameObject);
		}
		break;
		case E_Component_Type::E_COMPONENT_TYPE_UI_FILE_LIST_MENU:
		{
			return new FileListMenuComponent(pCreationData, pOwnerGameObject);
		}
		break;
		case E_Component_Type::E_COMPONENT_TYPE_UI_TEXT:
		{
			return new TextComponent(pCreationData, pOwnerGameObject);
		}
		break;
	}

	return nullptr;
}
