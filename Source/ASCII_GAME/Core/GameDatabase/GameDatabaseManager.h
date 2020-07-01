#ifndef _GAME_RESOURCE_MANAGER_H_
#define _GAME_RESOURCE_MANAGER_H_

#include "../Utils/Types.h"
#include "Factory/Factory.h"
#include "DatabaseTypes.h"
#include <map> 

class EntityCreate;
class C_ProjectSettings;

namespace GDb 
{
    
class C_GameDatabaseManager
{

public:
	
	static C_GameDatabaseManager* Instance();
	~C_GameDatabaseManager();

	void Initialise();
	bool ClassExistsInFactory(int hashcode);
	void LoadPakFile(const char* filename);
	void AssignDataPointer(int hashcode, C_DataItem** pGameDataBase);
    C_DataItem *GetItemPointerFromId(const int itemId){return m_GameDataMap[itemId];}
    
    template <class T>
    void RegisterClass(const char *className)
    {
        C_Hash32 hashCode(className);
        m_DataFactory.AddClass(hashCode.GetHashValue(), &Constructor<T>);
    }

	Factory<C_DataItem>& GetFactory() { return m_DataFactory;  }


	void AddEntity(EntityCreate* pEntity) { m_TempEntities.push_back(pEntity); }
	std::vector<EntityCreate*>* GetEntities() { return &m_TempEntities; }

	void SetProjectSettings(C_ProjectSettings* pSettings);
	const C_ProjectSettings* GetProjectSettings() const;

private:

	C_GameDatabaseManager();

	static C_GameDatabaseManager* m_pInstance;

	void LoadGameDataFromFile(const char* filename);

	Factory<C_DataItem> m_DataFactory;
	//classes are newed into m_GameDataMap
	std::map<int, C_DataItem*> m_GameDataMap;
	
	//game side references filled in by m_GameDataPointersMap
	std::map<int, C_DataItem**> m_GameDataPointersMap;

	std::vector<EntityCreate*> m_TempEntities;
	
	C_ProjectSettings* m_pProjectSettings;
};

} //namespace GDb

#endif //_GAME_RESOURCE_MANAGER_H_
