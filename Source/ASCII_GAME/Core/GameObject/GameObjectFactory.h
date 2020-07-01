#ifndef _GAME_OBJECT_FACTORY_H_
#define _GAME_OBJECT_FACTORY_H_

class GameObject;
class GameObjectCreate;

class GameObjectFactory
{
public:
	virtual ~GameObjectFactory() {}
	virtual GameObject* GetGameObject(const GameObjectCreate* pCreationData);
};

#endif
