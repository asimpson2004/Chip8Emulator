#include "ProjectSettings.h"
#include "GameDataHelpers.h"

//#include "../Context/SysContextProvider.h"
#include "GameDatabaseManager.h"

C_ProjectSettings::C_ProjectSettings()
{
}

C_ProjectSettings::~C_ProjectSettings()
{
}

void C_ProjectSettings::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_DefaultGameState, buffer);
	GDb::InitialiseFromBinary(&m_PauseMenuGameState, buffer);

	GDb::C_GameDatabaseManager* pGameDatabaseManager = GDb::C_GameDatabaseManager::Instance();
	pGameDatabaseManager->SetProjectSettings(this);
}
