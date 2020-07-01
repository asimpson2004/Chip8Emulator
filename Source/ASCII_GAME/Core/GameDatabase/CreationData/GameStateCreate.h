#ifndef _GAME_STATE_CREATE_H_
#define _GAME_STATE_CREATE_H_

#include <vector>
#include "../../GameState/GameStateManager.h"
#include "../DatabaseTypes.h"
#include "../GameDataHelpers.h"

class GameObjectCreate;

class GameStateCreate : public GDb::C_DataItem
{
public:
	GameStateCreate()
	{
	}

	virtual int GetGameStateType() const { return -1; }; // = 0
	int m_GameStateId;
	GDb::C_Array<GDb::C_Ref<GameObjectCreate>> m_GameObjects;

	virtual void InitialiseFromBinary(char*& buffer)
	{
		GDb::InitialiseFromBinary(&m_GameStateId, buffer);
		GDb::InitialiseFromBinary(&m_GameObjects, buffer);

		//GameStateManager::Instance()->RegisterGameStateCreationData(m_GameStateId, this);
	}
};

#endif
