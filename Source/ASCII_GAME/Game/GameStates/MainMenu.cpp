#include "MainMenu.h"

#include "../GameData/GameDatabase/CreationData/MainMenuGameStateCreate.h"

MainMenuGameState::MainMenuGameState(const GameStateCreate* pCreationData)
	:GameState(pCreationData)
{
	const MainMenuGameStateCreate* pManuStateCreationData = dynamic_cast<const MainMenuGameStateCreate*>(pCreationData);

	if (pManuStateCreationData)
	{	
		//load parameters from creation data as needed
	}
}

MainMenuGameState::~MainMenuGameState()
{
}

void MainMenuGameState::Update(float delta)
{
	GameState::Update(delta);
}

void MainMenuGameState::Render(ASCIIRenderer* pRenderer)
{
	GameState::Render(pRenderer);
}

void MainMenuGameState::OnSuspend()
{
}

void MainMenuGameState::OnResume()
{
}

void MainMenuGameState::OnMessage(Message* pMessage)
{
	if (pMessage == nullptr)
		return;

}
