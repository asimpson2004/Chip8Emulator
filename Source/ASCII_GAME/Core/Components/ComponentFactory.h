#ifndef _COMPONENT_FACTORY_H_
#define _COMPONENT_FACTORY_H_

class Component;
class ComponentCreate;
class GameObject;

class ComponentFactory
{
public:
	virtual Component* GetComponent(const ComponentCreate* pCreationData, GameObject* pOwnerGameObject);
};

#endif
