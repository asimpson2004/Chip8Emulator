#ifndef _GAME_OBJECT_CREATE_H_
#define _GAME_OBJECT_CREATE_H_

#include <vector>
#include "../Vector2D.h"
#include "../DatabaseTypes.h"
#include "ComponentCreate.h"


class GameObjectCreate : public GDb::C_DataItem
{
public:
	GameObjectCreate();
	virtual ~GameObjectCreate() {}
		
	virtual int GetGameObjectType() const { return 0; }

	int m_GameObjectId;
	GDb::C_Vector2d m_Position;
	GDb::C_Array<GDb::C_Pointer<ComponentCreate>> m_ComponentIds;

	//For programatic creation
	std::vector<ComponentCreate*> m_Components; 

	virtual void InitialiseFromBinary(char*& buffer);
};

#endif
