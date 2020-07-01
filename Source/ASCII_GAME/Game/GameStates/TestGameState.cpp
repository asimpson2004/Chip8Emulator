#include "TestGameState.h"
#include "../GameData/GameDatabase/CreationData/TestGameStateCreationData.h"

TestGameState::TestGameState(const GameStateCreate* pCreationData)
:GameState(pCreationData)
{
	const TestGameStateCreate* pTestGameStateCreate = dynamic_cast<const TestGameStateCreate*>(pCreationData);

	if (pTestGameStateCreate)
	{
		//load parameters from creation data as needed
	}
}

TestGameState::~TestGameState()
{
}

void TestGameState::Update(float delta)
{
	GameState::Update(delta);
}

void TestGameState::Render(ASCIIRenderer* pRenderer)
{
	GameState::Render(pRenderer);
}

void TestGameState::OnSuspend()
{

}

void TestGameState::OnResume()
{

}
