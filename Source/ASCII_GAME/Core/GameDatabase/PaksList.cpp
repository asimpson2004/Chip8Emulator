#include "PaksList.h"
#include "GameDataHelpers.h"

namespace GDb
{
C_PaksList::C_PaksList()
{

}

C_PaksList::~C_PaksList()
{
}

void C_PaksList::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_PakFileNames,		buffer);
}

}//namespace GDb
