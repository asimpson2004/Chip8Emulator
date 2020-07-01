#include "Chip8EmulatorGameState.h"

#include "../GameData/GameDatabase/CreationData/GameStates/Chip8EmulatorGameStateCreate.h"
#include "../GameData/GameDatabase/CreationData/Chip8EmulatorComponentCreate.h"

#include "../../Core/GameDatabase/CreationData/GameObjectCreate.h"
#include "../../Core/GameObject/GameObjectManager.h"

#include "../../Core/GameDatabase/GameDatabaseManager.h"
#include "../../Core/GameDatabase/ProjectSettings.h"

#include "../../Core/Input/InputManager.h"
#include "../../Core/Input/InputDevice.h"

Chip8EmulatorGameState::Chip8EmulatorGameState(const GameStateCreate* pCreationData)
	:GameState(pCreationData)
{
	const Chip8EmulatorGameStateCreate* pChip8EmulatorGameStateCreationData = dynamic_cast<const Chip8EmulatorGameStateCreate*>(pCreationData);

	if (pChip8EmulatorGameStateCreationData)
	{
		Chip8EmulatorComponentCreate chip8EmulatorComponentCreate;
		chip8EmulatorComponentCreate.filename = pChip8EmulatorGameStateCreationData->m_RomFilename;

		GameObjectCreate chip8EmulatorGameObject;
		chip8EmulatorGameObject.m_Components.push_back(&chip8EmulatorComponentCreate);

		GameObject* pGameObject = GameObjectManager::Instance()->GetGameObject(&chip8EmulatorGameObject);
		if (pGameObject)
		{
			AddGameObject(pGameObject);
		}
	}
}

Chip8EmulatorGameState::~Chip8EmulatorGameState()
{
}

void Chip8EmulatorGameState::Update(float delta)
{
	InputDevice* pInputDevice = InputManager::Instance()->GetInputDevice();

	if (pInputDevice && pInputDevice->GetButtonInput(E_DigitalInput_PAUSE).OnPressed())
	{
		const C_ProjectSettings* projectSettings = GDb::C_GameDatabaseManager::Instance()->GetProjectSettings();
		GameStateManager::Instance()->PushGameState(projectSettings->m_PauseMenuGameState.GetItem());
	}

	GameState::Update(delta);
}

void Chip8EmulatorGameState::Render(ASCIIRenderer* pRenderer)
{
	GameState::Render(pRenderer);

}

void Chip8EmulatorGameState::OnSuspend()
{
}

void Chip8EmulatorGameState::OnResume()
{
}
