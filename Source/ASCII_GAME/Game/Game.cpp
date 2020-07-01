#include "Game.h"

#include <chrono>

#include "../Core/Utils/Utils.h"
#include "../Core/Renderer/ASCIIRenderer.h"

#include "../Core/GameState/GameStateManager.h"
#include "GameStates/GameStateFactoryImpl.h"

#include "../Core/GameObject/GameObjectManager.h"
#include "GameObjects/GameObjectFactoryImpl.h"

#include "../Core/Components/ComponentManager.h"
#include "../Game/Components/ComponentFactoryImpl.h"

#include "../Core/GameDatabase/GameDatabaseManager.h"
#include "../Game/GameData/GameDatabase/GameDatabase.h"

#include "../Core/GameDatabase/ProjectSettings.h"

#include "../Core/Input/InputManager.h"
#include "Input/KeyboardAndMouseInputDevice.h"

const float GAME_UPDATE_FREQ = 1.0f / 60.0f;
const int SCREEN_WIDTH = 128;
const int SCREEN_HEIGHT = 32;

Game::Game()
:m_pRenderer(nullptr)
,m_bInitialised(false)
,m_bExitApp(false)
,m_deltaTime(0.0f)
{
	srand(0);

	GameObjectManager::Instance()->SetGameObjectFactory(new GameObjectFactoryImpl());
	ComponentManager::Instance()->SetComponentFactory(new ComponentFactoryImpl());

	m_pGameStateManager = GameStateManager::Instance();
	m_pGameStateManager->SetGameStateFactory(new GameStateFactoryImpl());


	GDb::C_GameDatabaseManager::Instance()->Initialise();

	C_GameDatabase::Instance()->Init(); //sits ontop of C_GameDatabaseManager

	InputManager::Instance()->Initialise();
	InputManager::Instance()->SetInputDevice(new KeyboardAndMouseInputDevice());
}

Game::~Game()
{
	SAFE_DELETE_PTR(m_pRenderer);
}

void Game::Initialise()
{
	InitialiseRenderer();

	const C_ProjectSettings* pProjectSettings = GDb::C_GameDatabaseManager::Instance()->GetProjectSettings();
	if (pProjectSettings)
	{
		m_pGameStateManager->PushGameState(pProjectSettings->m_DefaultGameState.GetItem());
	}

	m_bInitialised = true;
}

void Game::InitialiseRenderer()
{
	m_pRenderer = new ASCIIRenderer();

	m_pRenderer->Initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
}

void Game::Run()
{
	while (!m_bExitApp)
	{
		std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

		Update(m_deltaTime);

		Render();

		std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
		std::chrono::microseconds delta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		m_deltaTime = delta.count() * 0.000001f;

		
		while (m_deltaTime < GAME_UPDATE_FREQ)
		{
			endTime = std::chrono::high_resolution_clock::now();
			delta = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			m_deltaTime = delta.count() * 0.000001f;
		}
	}
}

void Game::Update(float delta)
{
	if (GetKeyState(VK_ESCAPE) < 0)
	{
		m_bExitApp = true;
		return;
	}

	InputManager::Instance()->Update();

	m_pGameStateManager->Update(delta);

}


void Game::Render()
{
	m_pRenderer->GetBackBufferLock().lock();
	m_pRenderer->ClearScreen();	

	m_pGameStateManager->Render(m_pRenderer);

	m_pRenderer->GetBackBufferLock().unlock();
}
