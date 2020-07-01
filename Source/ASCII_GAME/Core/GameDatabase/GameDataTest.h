#ifndef _GAME_DATA_TEST_H_
#define _GAME_DATA_TEST_H_

#include "DatabaseTypes.h"

#include <string>
#include <vector>

enum TestEnum
{
	ENUMTESTVAL_ONE,
	ENUMTESTVAL_TWO,
};

class GameDataTestMember : public GDb::C_DataItem
{
public:

	GameDataTestMember();
	virtual ~GameDataTestMember();

	virtual void InitialiseFromBinary(char*& buffer);

	int 		m_TestInt;
	const char*		m_TestString;

};

class GameDataTestChildA : public GameDataTestMember
{
public:
	GameDataTestChildA();
	virtual ~GameDataTestChildA();

	virtual void InitialiseFromBinary(char*& buffer);

	int 		m_TestChildInt;
};

class GameDataTestChildB : public GameDataTestMember
{
public:
	GameDataTestChildB();
	virtual ~GameDataTestChildB();

	virtual void InitialiseFromBinary(char*& buffer);

	float 		m_TestChildFloat;
};

class GameDataTest : public GDb::C_DataItem
{
public:

	GameDataTest();
	virtual ~GameDataTest();

	virtual void InitialiseFromBinary(char*& buffer);

	int 						m_TestInt;
	int 						m_TestInttwo;
	const char*					m_TestString;
	float						m_TestFloat;
	bool						m_TestBool;
	TestEnum 					m_TestEnum;
	GDb::C_Array<TestEnum>		m_TestEnumArray;
	GameDataTestMember			m_TestClass;
	GDb::C_Array<GameDataTestMember> m_TestClassArray;
	GDb::C_Ref<GameDataTestMember> m_TestClassRef;
	GameDataTestChildB			m_pChildClass;
};



#endif //_GAME_DATA_TEST_H_
