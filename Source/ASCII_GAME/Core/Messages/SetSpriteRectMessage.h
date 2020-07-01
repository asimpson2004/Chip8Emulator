#ifndef _SET_SPRITE_RECT_MESSAGE_H_
#define _SET_SPRITE_RECT_MESSAGE_H_

#include "Message.h"
#include "MessageType.h"
#include "../Maths/Rect.h"
#include "../Maths/Vector2.h"


class SetSpriteRectMessage : public Message
{
public:
	virtual ~SetSpriteRectMessage() {}

	virtual int GetMessageType() { return (int)E_MESSAGE_TYPE::SET_SPRITE_RECT;  }

	Rect SpriteRect;
	Vector2 SpriteOrigin;

};

#endif
