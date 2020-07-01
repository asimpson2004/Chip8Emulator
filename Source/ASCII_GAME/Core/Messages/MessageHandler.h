#ifndef _MESSAGE_HANDLER_H_
#define _MESSAGE_HANDLER_H_

class Message;

class MessageHandler
{
public:
	virtual void OnMessage(Message* pMessage) = 0;
};

#endif
