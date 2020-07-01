#ifndef _GAME_OBJECT_FACTORY_IMPL_H_
#define _GAME_OBJECT_FACTORY_IMPL_H_

#include "../../Core/GameObject/GameObjectFactory.h"

class GameObject;
class GameObjectCreate;

class GameObjectFactoryImpl : public GameObjectFactory
{
public:
	virtual ~GameObjectFactoryImpl() {}
	virtual GameObject* GetGameObject(GameObjectCreate* pCreationData);
};

#endif
