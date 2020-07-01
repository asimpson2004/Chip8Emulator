#include "GameStateFactoryImpl.h"

#include "../../Core/GameDatabase/CreationData/GameStateCreate.h"

#include "GameStateType.h"
#include "MainMenu.h"
#include "TestGameState.h"
#include "Chip8EmulatorGameState.h"

GameStateFactoryImpl::GameStateFactoryImpl()
{
}

GameStateFactoryImpl::~GameStateFactoryImpl()
{
}

GameState* GameStateFactoryImpl::GetGameState(const GameStateCreate* creationData)
{
	if (creationData)
	{
		switch (creationData->GetGameStateType())
		{
			case E_STATE_TYPE_MENU:
			{
				return new MainMenuGameState(creationData);
			}
			break;
			case E_STATE_TYPE_TEST:
			{
				return new TestGameState(creationData);
			}
			break;
			case E_STATE_TYPE_CHIP_8_EMULATOR:
			{
				return new Chip8EmulatorGameState(creationData);
			}
			break;
		}
	}

	return nullptr;
}
