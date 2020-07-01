#ifndef PROJECT_SETTINGS_H
#define PROJECT_SETTINGS_H

#include "DatabaseTypes.h"
#include "CreationData/GameStateCreate.h"

class C_ProjectSettings: public GDb::C_DataItem
{
public:

	C_ProjectSettings();
	virtual ~C_ProjectSettings();

	virtual void InitialiseFromBinary(char*& buffer);

	GDb::C_Ref<GameStateCreate> m_DefaultGameState;
	GDb::C_Ref<GameStateCreate> m_PauseMenuGameState;


};

#endif
