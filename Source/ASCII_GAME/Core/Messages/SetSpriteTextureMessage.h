#ifndef _SET_SPRITE_TEXTURE_MESSAGE_H_
#define _SET_SPRITE_TEXTURE_MESSAGE_H_

#include "Message.h"
#include "MessageType.h"
#include "../Maths/Rect.h"
#include "../Maths/Vector2.h"

class SetSpriteTextureMessage : public Message
{
public:
	virtual ~SetSpriteTextureMessage() {}

	virtual int GetMessageType() { return (int)E_MESSAGE_TYPE::SET_SPRITE_TEXTURE; }

	const char* TextureFilename;
	Rect SpriteRect;
	Vector2 SpriteOrigin;
};

#endif
