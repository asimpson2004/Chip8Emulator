#ifndef _ANIMATOR_COMPONENT_CREATE_H_
#define _ANIMATOR_COMPONENT_CREATE_H_

#include <vector>
#include "ComponentCreate.h"
#include "../../Components/ComponentType.h"


enum E_AnimationState
{
	E_AnimationState_Dash,
	E_AnimationState_Death,
	E_AnimationState_Dig,
	E_AnimationState_Hit,
	E_AnimationState_Holo,
	E_AnimationState_Idle,
	E_AnimationState_Melee,
	E_AnimationState_Sprint,
	E_AnimationState_TeleportIn,
	E_AnimationState_TeleportOut,
	E_AnimationState_Walk,

	E_AnimationState_MAX
};

class AnimationCreate : public GDb::C_DataItem
{
public:
	AnimationCreate() {};
	~AnimationCreate() {};

	virtual void InitialiseFromBinary(char*& buffer);

	E_AnimationState m_AnimationId;
	const char* m_Spritesheet;
	const char* m_AnimationName;
	int m_FPS;
	bool m_bLoop;
};

class AnimationSetCreate : public GDb::C_DataItem
{
public:
	AnimationSetCreate() {};
	~AnimationSetCreate() {};

	virtual void InitialiseFromBinary(char*& buffer);

	GDb::C_Array<AnimationCreate> m_Animations;
};

class AnimatorComponentCreate : public ComponentCreate
{
public:
	AnimatorComponentCreate() :m_DefaultAnimation(E_AnimationState_Idle){}
	~AnimatorComponentCreate() {}

	virtual void InitialiseFromBinary(char*& buffer);

	virtual AnimatorComponentCreate* Clone() const { return new AnimatorComponentCreate(*this); }

	virtual const int GetComponentType() const { return (int)E_Component_Type::E_COMPONENT_TYPE_ANIMATOR; }

	E_AnimationState m_DefaultAnimation;
	GDb::C_Ref<AnimationSetCreate> m_AnimationSet;

};


#endif
