#ifndef _SPRITE_COMPONENT_CREATE_H_
#define _SPRITE_COMPONENT_CREATE_H_

#include <Windows.h>
#include "ComponentCreate.h"
#include "../Vector2D.h"
#include "../../Components/ComponentType.h"

class SpriteComponentCreate : public ComponentCreate
{
public:
	SpriteComponentCreate()
	{}

	virtual const int GetComponentType() const { return (int)E_Component_Type::E_COMPONENT_TYPE_SPRITE; }

	GDb::C_Vector2d m_SpriteSize;
	int m_Layer;

	virtual void InitialiseFromBinary(char*& buffer);

	virtual SpriteComponentCreate* Clone() const { return new SpriteComponentCreate(*this); }

};


class SpriteComponentTextCreate : public SpriteComponentCreate
{
public:
	SpriteComponentTextCreate()
	{
	}
	virtual ~SpriteComponentTextCreate() {};

	int m_SpriteColour;
	char* m_Pixels;

	virtual void InitialiseFromBinary(char*& buffer);

	virtual SpriteComponentTextCreate* Clone() const { return new SpriteComponentTextCreate(*this); }

};

class SpriteComponentCharInfoCreate : public SpriteComponentCreate
{
public:
	SpriteComponentCharInfoCreate()
	{
	}
	virtual ~SpriteComponentCharInfoCreate() {};

	CHAR_INFO* m_Pixels;

	virtual void InitialiseFromBinary(char*& buffer);
	virtual SpriteComponentCharInfoCreate* Clone() const { return new SpriteComponentCharInfoCreate(*this); }

};

class SpriteComponentIntCreate : public SpriteComponentCreate
{
public:
	SpriteComponentIntCreate()
	{
	}
	virtual ~SpriteComponentIntCreate() {};

	int* m_Pixels;

	virtual void InitialiseFromBinary(char*& buffer);

	virtual SpriteComponentIntCreate* Clone() const { return new SpriteComponentIntCreate(*this); }

};

class SpriteComponentFileCreate : public SpriteComponentCreate
{
public:
	SpriteComponentFileCreate()
	:m_Filename("")
	{
	}
	virtual ~SpriteComponentFileCreate() {};

	const char* m_Filename;

	virtual void InitialiseFromBinary(char*& buffer);
	virtual SpriteComponentFileCreate* Clone() const { return new SpriteComponentFileCreate(*this); }

};

#endif
