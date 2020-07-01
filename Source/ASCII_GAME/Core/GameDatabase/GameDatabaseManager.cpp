#include "GameDatabaseManager.h"
#include "../Utils/Utils.h"
#include "GameDataTest.h"
#include "PaksList.h"
#include "../Platform/IO/File.h"

#include "Vector2D.h"

//Project Settings
#include "ProjectSettings.h"
//GameState
#include "CreationData/GameStateCreate.h"
//Entity
#include "CreationData/GameObjectCreate.h"
//Components
#include "CreationData/ComponentCreate.h"
#include "CreationData/SpriteComponentCreate.h"
#include "CreationData/AnimatorComponentCreate.h"
#include "CreationData/BoxColliderComponentCreate.h"

//UI Components
#include "CreationData/UI/TextAlignmentType.h"
#include "CreationData/UI/ListMenuComponentCreate.h"
#include "CreationData/UI/FileListMenuComponentCreate.h"
#include "CreationData/UI/TextComponentCreate.h"

namespace GDb 
{

C_PaksList* pPaksList = nullptr;
GameDataTest* pGameDataTest = nullptr;

C_GameDatabaseManager* C_GameDatabaseManager::m_pInstance = nullptr;

C_GameDatabaseManager* C_GameDatabaseManager::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new C_GameDatabaseManager();
	}

	return m_pInstance;
}
    
C_GameDatabaseManager::C_GameDatabaseManager()
:m_pProjectSettings(nullptr)
{

}

C_GameDatabaseManager::~C_GameDatabaseManager()
{
	for (std::map<int, C_DataItem*>::iterator it = m_GameDataMap.begin(); it != m_GameDataMap.end(); ++it)
	{
		SAFE_DELETE_PTR(it->second);
	}
}

void C_GameDatabaseManager::Initialise()
{
    RegisterClass<C_PaksList>("PaksList");    
	C_Hash32 PakListHashCode("PaksList");
	AssignDataPointer(PakListHashCode.GetHashValue(), (C_DataItem**)&pPaksList);

	/*TEST*/
	RegisterClass<TestEnum>("TestEnum");
	RegisterClass<GameDataTestMember>("GameDataTestMember");
	RegisterClass<GameDataTestChildA>("GameDataTestChildA");
	RegisterClass<GameDataTestChildB>("GameDataTestChildB");
	RegisterClass<GameDataTest>("GameDataTest");
	C_Hash32 GameDataTestHashCode("GameDataTest");
	AssignDataPointer(GameDataTestHashCode.GetHashValue(), (C_DataItem**)&pGameDataTest);
	/*~TEST*/

	//vector
	RegisterClass<C_Vector2d>("Vector2d");

	//Entity
	RegisterClass<GameObjectCreate>("GameObject");

	//Components
	RegisterClass<ComponentCreate>("Component");

	RegisterClass<SpriteComponentCreate>("SpriteComponent");
	RegisterClass<SpriteComponentFileCreate>("SpriteComponentFile");

	RegisterClass<E_AnimationState>("AnimationState");
	RegisterClass<AnimationCreate>("Animation");
	RegisterClass<AnimationSetCreate>("AnimationSet");
	RegisterClass<AnimatorComponentCreate>("AnimatorComponent");

	RegisterClass<BoxColliderComponentCreate>("BoxColliderComponent");

	//UI Components
	RegisterClass<E_TextAlignmentType>("E_TextAlignment");
	RegisterClass<MenuItemCreate>("MenuItem");
	RegisterClass<ListMenuComponentCreate>("ListMenuComponent");
	RegisterClass<FileListMenuComponentCreate>("FileListMenuComponent");
	RegisterClass<TextComponentCreate>("TextComponent");

	//Game States
	RegisterClass<GameStateCreate>("GameState");

	//Project Settings
	RegisterClass<C_ProjectSettings>("ProjectSettings");
}

void C_GameDatabaseManager::SetProjectSettings(C_ProjectSettings* pSettings)
{
	m_pProjectSettings = pSettings;
}

const C_ProjectSettings* C_GameDatabaseManager::GetProjectSettings() const
{
	return m_pProjectSettings;
}

void C_GameDatabaseManager::LoadPakFile(const char *fname)
{
	LoadGameDataFromFile(fname);

	if(pPaksList)
	{
		C_Array<const char*>::iterator iterator = pPaksList->m_PakFileNames.begin();
		while ( iterator != pPaksList->m_PakFileNames.end() )
		{
			LoadGameDataFromFile( (*iterator) );
			++iterator;
		}
	}
}

void C_GameDatabaseManager::LoadGameDataFromFile(const char* filename)
{
	iofileType gameDataFile;
	gameDataFile.Open(filename);

	unsigned int fileLength = gameDataFile.Length();

	char* buffer = new char[fileLength];

	gameDataFile.ReadBytes(fileLength, buffer);

	int numItems = 0;	

	char* pBuffer = buffer;
	
	memcpy( &numItems, pBuffer, sizeof(int) );
	pBuffer+=sizeof(int);

	for(int i = 0; i < numItems; i++)
	{
		unsigned int hashcode;
		int itemID;

		memcpy( &hashcode, pBuffer, sizeof(int) );

		pBuffer+=sizeof(int);

		memcpy( &itemID, pBuffer, sizeof(int) );

		pBuffer+=sizeof(int);

		C_DataItem* pClass = m_DataFactory.ConstructClass(hashcode);

		//ASSERT(pClass != nullptr); // Class not been registered - maybe we should skip it?	

		pClass->InitialiseFromBinary(pBuffer);

		m_GameDataMap[itemID] = pClass;

		if(m_GameDataPointersMap.count(hashcode) > 0)
		{
			(*m_GameDataPointersMap[hashcode]) = m_GameDataMap[itemID];
		}
	}

	SAFE_DELETE_PTR(buffer);
	
}

bool C_GameDatabaseManager::ClassExistsInFactory(int hashcode)
{
	return m_DataFactory.IsClassInFactory(hashcode);
}

void C_GameDatabaseManager::AssignDataPointer(int hashcode, C_DataItem** pGameDataBase)
{
	m_GameDataPointersMap[hashcode] = pGameDataBase;
}
    
}//namespace GDb 
