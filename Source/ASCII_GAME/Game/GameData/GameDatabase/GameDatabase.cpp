#include "GameDatabase.h"

#include "../../../Core/GameDatabase/GameDatabaseManager.h"

//Game States
#include "CreationData/MainMenuGameStateCreate.h"
#include "CreationData/TestGameStateCreationData.h"
#include "CreationData/Chip8EmulatorComponentCreate.h"
#include "CreationData/UI/Chip8GameStateLauncherComponentCreate.h"
#include "CreationData/UI/PauseMenuControllerComponentCreate.h"
#include "CreationData/GameStates/Chip8EmulatorGameStateCreate.h"

C_GameDatabase* C_GameDatabase::m_pInstance = nullptr;

C_GameDatabase::C_GameDatabase()
{
}

C_GameDatabase* C_GameDatabase::Instance()
{
    if (m_pInstance == nullptr)
    {
        m_pInstance = new C_GameDatabase();
    }

    return m_pInstance;
}

// Register members of the game database
bool C_GameDatabase::Init(void)
{
    GDb::C_GameDatabaseManager* pGameDatabaseManager = GDb::C_GameDatabaseManager::Instance();

    // Register database classes
    
	//Game States
    pGameDatabaseManager->RegisterClass<MainMenuGameStateCreate>("MainMenuGameState");
	pGameDatabaseManager->RegisterClass<TestGameStateCreate>("TestGameState");
    pGameDatabaseManager->RegisterClass<Chip8EmulatorGameStateCreate>("Chip8EmulatorGameState");

    //Game Components
    pGameDatabaseManager->RegisterClass<Chip8EmulatorComponentCreate>("Chip8EmulatorComponent");
    pGameDatabaseManager->RegisterClass<Chip8GameStateLauncherComponentCreate>("Chip8GameStateLauncherComponent");
    pGameDatabaseManager->RegisterClass<PauseMenuComponentControllerComponentCreate>("PauseMenuComponentControllerComponent");
        
	// Load Pak files listed in Paks.pak
    pGameDatabaseManager->LoadPakFile("Paks.pak" );

    return true;
}

void InitialiseTagFromBinary(const char** pStr, char*& buffer)
{
	unsigned int strlen = 0;
	memcpy( &strlen, buffer, sizeof(int) );
	buffer += sizeof(int);
    
	int size = strlen;
    
	char *destStr = (char *) malloc(size);
    char *destStrPtr = destStr;
    
    // copy string across skipping whitespace
    for(int i=0;i<size;i++)
    {
        if(*buffer != ' ')
            *destStrPtr++ = *buffer;
        buffer++;
    }
    
    (*pStr) = destStr;
}
