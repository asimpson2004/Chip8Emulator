#include "SpriteComponentCreate.h"

#include "../GameDataHelpers.h"

void SpriteComponentCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_SpriteSize, buffer);
	GDb::InitialiseFromBinary(&m_Layer, buffer);

	ComponentCreate::InitialiseFromBinary(buffer);
}

void SpriteComponentTextCreate::InitialiseFromBinary(char*& buffer)
{
	//do later
}

void SpriteComponentCharInfoCreate::InitialiseFromBinary(char*& buffer)
{
	//do later
}

void SpriteComponentIntCreate::InitialiseFromBinary(char*& buffer)
{
	//do later
}

void SpriteComponentFileCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_Filename, buffer);

	SpriteComponentCreate::InitialiseFromBinary(buffer);
}