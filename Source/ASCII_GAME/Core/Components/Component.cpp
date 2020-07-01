#include "Component.h"
#include "../GameObject/GameObject.h"
#include "../Messages/MessageManager.h"
#include "ComponentManager.h"
#include "../GameDatabase/CreationData/ComponentCreate.h"

Component::Component(const ComponentCreate* pCreationData, GameObject* pOwner)
:m_pCreationData(pCreationData)
,m_pOwner(pOwner)
{
}

Component::~Component()
{
}

void Component::BroadcastMessageToGameObject(Message* pMessage)
{
	m_pOwner->OnMessage(pMessage);
}

void Component::BroadcastMessage(Message* pMessage)
{
	MessageManager::Instance()->BroadcastMessage(pMessage);
}

void Component::SubscribeToMessage(int messageType, MessageHandler* pMesssageHandler)
{
	MessageManager::Instance()->Subscribe(messageType, pMesssageHandler);
}

void Component::UnsubscribeFromMessage(int messageType, MessageHandler* pMesssageHandler)
{
	MessageManager::Instance()->Unsubscribe(messageType, pMesssageHandler);
}
