#ifndef _TEST_GAME_STATE_CREATION_DATA_H_
#define _TEST_GAME_STATE_CREATION_DATA_H_

#include "../../../../Core/GameDatabase/CreationData/GameStateCreate.h"
#include "../../../GameStates/GameStateType.h"

class TestGameStateCreate : public GameStateCreate
{
public:

	TestGameStateCreate()
	{
	}

	virtual int GetGameStateType() const { return E_STATE_TYPE_TEST; }

	int m_PlayerShipObjectId;
	int m_PlayerShipSpriteId;
	GDb::C_Ref<GameStateCreate> m_PauseMenuCreate;

	virtual void InitialiseFromBinary(char*& buffer)
	{
		GDb::InitialiseFromBinary(&m_PlayerShipObjectId, buffer);
		GDb::InitialiseFromBinary(&m_PlayerShipSpriteId, buffer);

		GameStateCreate::InitialiseFromBinary(buffer);
	}
};

#endif
