#include "GameObjectFactory.h"
#include "../GameDatabase/CreationData/GameObjectCreate.h"
#include "GameObject.h"

GameObject* GameObjectFactory::GetGameObject(const GameObjectCreate* pCreationData)
{
	if (pCreationData)
	{
		switch (pCreationData->GetGameObjectType())
		{
			case 0:
			{
				return new GameObject(pCreationData);
			}
		}
	}

	return nullptr;
}

