#ifndef _FILE_LIST_MENU_COMPONENT_
#define _FILE_LIST_MENU_COMPONENT_

#include "../../../Core/Components/UI/ListMenuComponent.h"

class ComponentCreate;
class GameObject;

class FileListMenuComponent : public ListMenuComponent
{
public:
	FileListMenuComponent(const ComponentCreate* pComponentCreate, GameObject* pOwner);
	virtual ~FileListMenuComponent();

	virtual void Initialise();
};

#endif
