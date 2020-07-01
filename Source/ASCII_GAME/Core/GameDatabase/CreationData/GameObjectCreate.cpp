#include "GameObjectCreate.h"
#include "../../GameObject/GameObjectManager.h"

#include "../GameDataHelpers.h"

GameObjectCreate::GameObjectCreate()
:m_GameObjectId(-1)
{
}

void GameObjectCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_GameObjectId, buffer);
	GDb::InitialiseFromBinary(&m_Position, buffer);
	GDb::InitialiseFromBinary(&m_ComponentIds, buffer);

	//GameObjectManager::Instance()->RegisterGameObjectCreationData(m_GameObjectId, this);
}