#ifndef _COMPONENT_H_
#define _COMPONENT_H_

class GameObject;
class Message;
class MessageHandler;
class ASCIIRenderer;
class ComponentCreate;

class Component
{
public:
	Component(const ComponentCreate* pCreationData, GameObject* pOwner);
	virtual ~Component();

	virtual void Initialise() {}
	virtual void Update(float delta) {}
	virtual void Render(ASCIIRenderer* pRenderer) {}
	virtual void OnMessage(Message* pMessage) {}

protected:
	void SubscribeToMessage(int messageType, MessageHandler* pMesssageHandler);
	void UnsubscribeFromMessage(int messageType, MessageHandler* pMesssageHandler);
	void BroadcastMessageToGameObject(Message* pMessage);
	void BroadcastMessage(Message* pMessage);

	const ComponentCreate* m_pCreationData;
	GameObject* m_pOwner;
};

#endif
