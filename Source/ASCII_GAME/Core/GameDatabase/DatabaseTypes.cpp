#include "GameDatabaseManager.h"

#include "DatabaseTypes.h"

namespace GDb
{
    
C_DataItem::C_DataItem()
{

}

C_DataItem::~C_DataItem()
{

}

C_VDataItem::C_VDataItem()
{

}

C_VDataItem::~C_VDataItem()
{

}

void *GetDataFromID(const unsigned int dataId)
{
    C_GameDatabaseManager* pGameDatabaseManager = C_GameDatabaseManager::Instance();
    
    if(pGameDatabaseManager)
    {
        return pGameDatabaseManager->GetItemPointerFromId(dataId);
    }    
    
    return nullptr;
}

    
}//namespace GDb