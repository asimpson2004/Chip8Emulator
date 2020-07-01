#include "AnimatorComponentCreate.h"
#include "../GameDataHelpers.h"

void AnimationCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_AnimationId, buffer);
	GDb::InitialiseFromBinary(&m_Spritesheet, buffer);
	GDb::InitialiseFromBinary(&m_AnimationName, buffer);
	GDb::InitialiseFromBinary(&m_FPS, buffer);
	GDb::InitialiseFromBinary(&m_bLoop, buffer);
}

void AnimationSetCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_Animations, buffer);
}

void AnimatorComponentCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_DefaultAnimation, buffer);
	GDb::InitialiseFromBinary(&m_AnimationSet, buffer);
	ComponentCreate::InitialiseFromBinary(buffer);
}
