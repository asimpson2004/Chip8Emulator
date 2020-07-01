#ifndef _BOX_COLLIDER_COMPONENT_H_
#define _BOX_COLLIDER_COMPONENT_H_

#include "../Component.h"

class BoxColliderComponentCreate;
class GameObject;

class BoxColliderComponent : public Component
{
public:
	BoxColliderComponent(BoxColliderComponentCreate* pBoxColliderComponentCreate, GameObject* pOwner);
	virtual ~BoxColliderComponent();
};

#endif
