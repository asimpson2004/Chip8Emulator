#ifndef _MESSAGE_MANAGER_H_
#define _MESSAGE_MANAGER_H_

#include <map>
#include <vector>

class Message;
class MessageHandler;

class MessageManager
{
public:
	~MessageManager();
	static MessageManager* Instance();

	void Subscribe(int messageId, MessageHandler* pMessageHandler);
	void Unsubscribe(int messageId, MessageHandler* pMessageHandler);
	void BroadcastMessage(Message* pMessage);

private:
	MessageManager();

	static MessageManager* m_pInstance;

	std::map<int, std::vector<MessageHandler*> > m_Subscribers;
};

#endif
