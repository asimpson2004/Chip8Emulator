#include "GameObjectFactoryImpl.h"
#include "../../Core/GameDatabase/CreationData/GameObjectCreate.h"

GameObject* GameObjectFactoryImpl::GetGameObject(GameObjectCreate* pCreationData)
{
	//Create custom game objects here

	return GameObjectFactory::GetGameObject(pCreationData);
}
