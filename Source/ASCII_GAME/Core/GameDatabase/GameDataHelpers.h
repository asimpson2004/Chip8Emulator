#ifndef _GAME_DATA_HELPERS_H_
#define _GAME_DATA_HELPERS_H_

#include "GameDatabaseManager.h"
#include "DatabaseTypes.h"

#include <string>
#include <vector>

namespace GDb
{

//int
static void InitialiseFromBinary(int* pInt, char*& buffer)
{
	memcpy( pInt, buffer, sizeof(int) );
	buffer += sizeof(int);
}

//float
static void InitialiseFromBinary(float* pFloat, char*& buffer)
{
	memcpy( pFloat, buffer, sizeof(float) );
	buffer += sizeof(float);
}

//bool
static void InitialiseFromBinary(bool* pBool, char*& buffer)
{
	memcpy( pBool, buffer, sizeof(bool) );
	buffer += sizeof(bool);
}

//class
static void InitialiseFromBinary(C_DataItem* pGameDataBase, char*& buffer)
{
	int hashcode = 0;
	memcpy( &hashcode, buffer, sizeof(int) );
	buffer += sizeof(int); 

	int itemID = 0;
	memcpy( &itemID, buffer, sizeof(int) );
	buffer += sizeof(int); 

	pGameDataBase->InitialiseFromBinary(buffer);
}

//string
static void InitialiseFromBinary(const char** pStr, char*& buffer)
{
	unsigned int strlen = 0;
	memcpy( &strlen, buffer, sizeof(int) );
	buffer += sizeof(int);

	int size = strlen;

	//char* str = 0;

	//if ( (pStr) ) { free( (pStr) ); }
	(*pStr) = (char *) malloc(size);
	//memset( (*pStr), 0, size );

	memcpy((char *) (*pStr), buffer, size);
	buffer += (size);
}

//enums or classes
template<class type> 
static void InitialiseFromBinary(type* pType, char*& buffer)
{
	int hashcode = 0;
	memcpy( &hashcode, buffer, sizeof(int) );

	C_GameDatabaseManager* pGameDatabaseManager = C_GameDatabaseManager::Instance();

	if(pGameDatabaseManager && pGameDatabaseManager->ClassExistsInFactory(hashcode))
	{
		//don't want to move the buffer on here
		InitialiseFromBinary((C_DataItem *) pType, buffer);
	}
	else
	{
		memcpy( pType, buffer, sizeof(type) );
		buffer += sizeof(type);
	}
}

//vectors
template<class type> 
static void InitialiseFromBinary(C_Array<type>* pVector, char*& buffer)
{
	unsigned int size = 0;
	memcpy( &size, buffer, sizeof(int) );
	buffer += sizeof(int);

	pVector->reserve(size);
	for(unsigned int i = 0; i < size; i++)
	{
		type temp;
		InitialiseFromBinary(&temp, buffer);
		pVector->push_back(temp);
	}
}
    
// references
template <class type>
static void InitialiseFromBinary(C_Ref<type>* pRef, char*& buffer)
{
    // get item id
	memcpy( &pRef->m_ItemId, buffer, sizeof(unsigned int) );
	buffer += sizeof(int);
}

//Pointers
template <class type>
static void InitialiseFromBinary(C_Pointer<type>* pPointer, char*& buffer)
{
	// get item hashcode
	memcpy(&pPointer->m_Hashcode, buffer, sizeof(unsigned int));
	buffer += sizeof(int);

	C_GameDatabaseManager* pGameDatabaseManager = C_GameDatabaseManager::Instance();
	//Make sure the class is in the factory
	if (pGameDatabaseManager && pGameDatabaseManager->ClassExistsInFactory(pPointer->m_Hashcode))
	{
		//create the new instance of the class and store it in the pointer;
		pPointer->m_pData = (GDb::C_VDataItem*)pGameDatabaseManager->GetFactory().ConstructClass(pPointer->m_Hashcode);

		//Initialise the class
		InitialiseFromBinary(pPointer->m_pData, buffer);

		//store the pointer in the C_Pointer
	}
	else
	{
		buffer += sizeof(type); //Doh...
	}

}


}; // GameDataHelpers

#endif //_GAME_DATA_HELPERS_H_
