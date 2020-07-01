#include "GameObjectManager.h"
#include "../Utils/Utils.h"

#include "GameObjectFactory.h"

GameObjectManager* GameObjectManager::m_pInstance = nullptr;

GameObjectManager::GameObjectManager()
	:m_pGameObjectFactory(nullptr)
{

}

GameObjectManager::~GameObjectManager()
{
	SAFE_DELETE_PTR(m_pGameObjectFactory);
}

GameObjectManager* GameObjectManager::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameObjectManager();
	}

	return m_pInstance;
}
/*
void GameObjectManager::RegisterGameObjectCreationData(int gameObjectId, GameObjectCreate* pGameObjectCreate)
{
	if (pGameObjectCreate == nullptr)
		return;

	std::map<int, GameObjectCreate*>::const_iterator it = m_GameObjectCreationData.find(gameObjectId);
	if (it != m_GameObjectCreationData.end())
	{
		return;
	}

	m_GameObjectCreationData.insert({ gameObjectId, pGameObjectCreate });
}

GameObjectCreate* GameObjectManager::GetGameObjectCreationData(int gameObjectId)
{
	std::map<int, GameObjectCreate*>::const_iterator it = m_GameObjectCreationData.find(gameObjectId);
	if (it != m_GameObjectCreationData.end())
	{
		return it->second;
	}

	return nullptr;
}
*/

GameObject* GameObjectManager::GetGameObject(const GameObjectCreate* pGameObjectCreate)
{
	//GameObjectCreate* pGameObjectCreate = GetGameObjectCreationData(gameObjectId);

	if (pGameObjectCreate)
	{
		if (m_pGameObjectFactory)
		{
			return m_pGameObjectFactory->GetGameObject(pGameObjectCreate);
		}
	}

	return nullptr;
}
