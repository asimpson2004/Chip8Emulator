#include "GameDataTest.h"
#include "GameDataHelpers.h"

GameDataTest::GameDataTest() 
:m_TestInt(0)
,m_TestFloat(0.0f)
,m_TestBool(false)
{
}

GameDataTest::~GameDataTest()
{

}

void GameDataTest::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_TestInt,		buffer);
	GDb::InitialiseFromBinary(&m_TestInttwo,	buffer);
	GDb::InitialiseFromBinary(&m_TestString,	buffer);
	GDb::InitialiseFromBinary(&m_TestFloat,		buffer);
	GDb::InitialiseFromBinary(&m_TestBool,		buffer);
	GDb::InitialiseFromBinary(&m_TestEnum,		buffer);
	GDb::InitialiseFromBinary(&m_TestEnumArray, buffer);
	GDb::InitialiseFromBinary(&m_TestClass,		buffer);
	GDb::InitialiseFromBinary(&m_TestClassArray, buffer);
	GDb::InitialiseFromBinary(&m_TestClassRef, buffer);
	GDb::InitialiseFromBinary(&m_pChildClass, buffer);
}

GameDataTestMember::GameDataTestMember():m_TestInt(0)
{
}

GameDataTestMember::~GameDataTestMember() 
{
}

void GameDataTestMember::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_TestInt,		buffer);
	GDb::InitialiseFromBinary(&m_TestString,	buffer);
}


GameDataTestChildA::GameDataTestChildA()
{

}

GameDataTestChildA::~GameDataTestChildA()
{

}

void GameDataTestChildA::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_TestChildInt, buffer);
	
	GameDataTestMember::InitialiseFromBinary(buffer);
}

GameDataTestChildB::GameDataTestChildB()
{

}

GameDataTestChildB::~GameDataTestChildB()
{

}

void GameDataTestChildB::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_TestChildFloat, buffer);
	
	GameDataTestMember::InitialiseFromBinary(buffer);
}

