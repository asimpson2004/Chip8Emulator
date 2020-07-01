#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include <vector>
#include "../Maths/Vector2.h"

#include "../Messages/MessageHandler.h"

class ASCIIRenderer;
class GameObject;
class GameStateCreate;

class GameState : public MessageHandler
{
public:
	GameState(const GameStateCreate* pCreationData);
	virtual ~GameState();

	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnSuspend() = 0;
	virtual void OnResume() = 0;

	void AddGameObject(GameObject* pGameObject);

protected:

	Vector2 m_Position;
	std::vector<GameObject*> m_GameObjects;
};

#endif
