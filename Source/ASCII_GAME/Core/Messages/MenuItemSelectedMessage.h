#ifndef _MENU_ITEM_SELECTED_MESSAGE_H_
#define _MENU_ITEM_SELECTED_MESSAGE_H_

#include "Message.h"
#include "MessageType.h"
#include <string>


class MenuItemSelectedMessage : public Message
{
public:
	virtual ~MenuItemSelectedMessage() {}

	virtual int GetMessageType() { return (int)E_MESSAGE_TYPE::MENU_ITEM_SELECTED; }

	std::string m_MenuItem;

};

#endif
