#ifndef _MAIN_MENU_GAME_STATE_CREATE_H_
#define _MAIN_MENU_GAME_STATE_CREATE_H_

#include "../../../../Core/GameDatabase/CreationData/GameStateCreate.h"
#include "../../../../Core/GameDatabase/Vector2D.h"
#include "../../../GameStates/GameStateType.h"

class MainMenuGameStateCreate : public GameStateCreate
{
public:

	MainMenuGameStateCreate()
	{
	}

	virtual int GetGameStateType() const { return (int)E_STATE_TYPE_MENU; }

	GDb::C_Vector2d m_TitlePosition;
	int m_SpriteId;

	virtual void InitialiseFromBinary(char*& buffer)
	{
		GDb::InitialiseFromBinary(&m_TitlePosition, buffer);
		GDb::InitialiseFromBinary(&m_SpriteId, buffer);

		GameStateCreate::InitialiseFromBinary(buffer);
	}

};

#endif
