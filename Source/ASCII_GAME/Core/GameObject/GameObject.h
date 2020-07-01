#ifndef _GAME_OBJECT_H_
#define _GAME_OBJECT_H_

#include <vector>
#include "../Maths/Vector2.h"

class ASCIIRenderer;
class Component;
class GameObjectCreate;
class Message;

class GameObject
{
public:
	GameObject(const GameObjectCreate* pCreationData);
	virtual ~GameObject();

	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);


	void BroadcastMessage(Message* pMessage);
	void OnMessage(Message* pMessage);

private:

	Vector2 m_Position;
	std::vector<Component*> m_Components;

};

#endif
