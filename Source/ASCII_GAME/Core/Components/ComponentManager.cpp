#include "ComponentManager.h"
#include "ComponentFactory.h"
#include "../Utils/Utils.h"

ComponentManager* ComponentManager::m_pInstance = nullptr;

ComponentManager::ComponentManager()
:m_pComponentFactory(nullptr)
{
}

ComponentManager::~ComponentManager()
{
	SAFE_DELETE_PTR(m_pComponentFactory);
}

ComponentManager* ComponentManager::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new ComponentManager();
	}

	return m_pInstance;
}

Component* ComponentManager::GetComponent(const ComponentCreate* pComponentCreate, GameObject* pOwnerObject)
{
	if (pComponentCreate)
	{
		if (m_pComponentFactory)
		{
			return m_pComponentFactory->GetComponent(pComponentCreate, pOwnerObject);
		}
	}

	return nullptr;
}
