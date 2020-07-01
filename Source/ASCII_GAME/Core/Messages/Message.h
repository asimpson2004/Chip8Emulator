#ifndef _MESSAGE_H_
#define _MESSAGE_H_

class Message
{
public:
	virtual int GetMessageType() = 0;
	virtual ~Message() {}

};

#endif
