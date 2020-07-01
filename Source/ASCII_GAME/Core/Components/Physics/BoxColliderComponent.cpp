#include "BoxColliderComponent.h"

#include "../../GameDatabase/CreationData/BoxColliderComponentCreate.h"

BoxColliderComponent::BoxColliderComponent(BoxColliderComponentCreate* pBoxColliderComponentCreate, GameObject* pOwner)
	:Component(pBoxColliderComponentCreate, pOwner)
{
}

BoxColliderComponent::~BoxColliderComponent()
{
}
