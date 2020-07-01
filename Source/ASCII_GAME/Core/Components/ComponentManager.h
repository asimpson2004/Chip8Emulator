#ifndef _COMPONENT_MANAGER_H_
#define _COMPONENT_MANAGER_H_

class Component;
class ComponentCreate;
class ComponentFactory;
class GameObject;

class ComponentManager
{
public:
	static ComponentManager* Instance();
	~ComponentManager();

	Component* GetComponent(const ComponentCreate* pComponentCreate, GameObject* pOwnerObject);

	void SetComponentFactory(ComponentFactory* pComponentFactory) { m_pComponentFactory = pComponentFactory; }

private:
	ComponentManager();

	static ComponentManager* m_pInstance;

	ComponentFactory* m_pComponentFactory;
};

#endif
