#ifndef _COMPONENT_FACTORY_IMPL_H_
#define _COMPONENT_FACTORY_IMPL_H_

#include "../../Core/Components/ComponentFactory.h"

class ComponentCreate;
class GameObject;

class ComponentFactoryImpl : public ComponentFactory
{
public:
	virtual Component* GetComponent(const ComponentCreate* pCreationData, GameObject* pOwnerGameObject);
};

#endif
