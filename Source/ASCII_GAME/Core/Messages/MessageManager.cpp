#include "MessageManager.h"
#include "MessageHandler.h"
#include "Message.h"

MessageManager* MessageManager::m_pInstance = nullptr;

MessageManager::MessageManager()
{
}

MessageManager::~MessageManager()
{
}

MessageManager* MessageManager::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new MessageManager();
	}

	return m_pInstance;
}

void MessageManager::Subscribe(int messageId, MessageHandler* pMessageHandler)
{
	m_Subscribers[messageId].push_back(pMessageHandler);
}

void MessageManager::Unsubscribe(int messageId, MessageHandler* pMessageHandler)
{
	for (std::vector<MessageHandler*>::iterator it = m_Subscribers[messageId].begin(); it != m_Subscribers[messageId].end(); ++it)
	{
		if ((*it) == pMessageHandler)
		{
			it = m_Subscribers[messageId].erase(it);
		}
	}
		
}

void MessageManager::BroadcastMessage(Message* pMessage)
{
	const int messageType = pMessage->GetMessageType();

	for (std::vector<MessageHandler*>::iterator it = m_Subscribers[messageType].begin(); it != m_Subscribers[messageType].end(); ++it)
	{
		(*it)->OnMessage(pMessage);
	}
}
