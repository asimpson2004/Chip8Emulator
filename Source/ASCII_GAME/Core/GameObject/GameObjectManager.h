#ifndef _GAME_OBJECT_MANAGER_H_
#define _GAME_OBJECT_MANAGER_H_

#include <map>

class GameObjectCreate;
class GameObjectFactory;
class GameObject;

class GameObjectManager
{
public:
	static GameObjectManager* Instance();
	~GameObjectManager();

	//void RegisterGameObjectCreationData(int gameObjectId, GameObjectCreate* pGameObjectCreate);
	//GameObject* GetGameObject(int gameObjectId);
	GameObject* GetGameObject(const GameObjectCreate* pGameObjectCreate);


	void SetGameObjectFactory(GameObjectFactory* pGameObjectFactory) { m_pGameObjectFactory = pGameObjectFactory; }

private:
	GameObjectManager();
	//GameObjectCreate* GetGameObjectCreationData(int gameObjectId);

	static GameObjectManager* m_pInstance;

	//std::map<int, GameObjectCreate*> m_GameObjectCreationData;

	GameObjectFactory* m_pGameObjectFactory;
};

#endif
