#include "GameStateManager.h"
#include "GameState.h"
#include "../Utils/Utils.h"
#include "../GameDatabase/CreationData/GameStateCreate.h"
#include "GameStateFactory.h"

GameStateManager* GameStateManager::m_pInstance = nullptr;

GameStateManager::GameStateManager()
:m_ReplacementGameState(nullptr)
,m_pGameStateFactory(nullptr)
{

}

GameStateManager::~GameStateManager()
{
	for (unsigned int i = 0; i < m_GameStates.size(); i++)
	{
		GameState* pGameState = m_GameStates.back();
		m_GameStates.pop_back();
		SAFE_DELETE_PTR(pGameState);
	}

	SAFE_DELETE_PTR(m_pGameStateFactory);
}

void GameStateManager::Update(float delta)
{
	if (m_GameStates.size() > 0)
	{
		m_GameStates.back()->Update(delta);
	}
}

void GameStateManager::Render(ASCIIRenderer* pRenderer)
{
	if (m_GameStates.size() > 0)
	{
		m_GameStates.back()->Render(pRenderer);

		if (m_bPopGameState.size() > 0)
		{			
			PerformPopGameState();
			if (m_ReplacementGameState != nullptr)
			{
				PerformReplaceGameState();
			}
		}
	}
}

void GameStateManager::PerformPopGameState()
{
	m_bPopGameState.pop_back();

	GameState* pGameState = m_GameStates.back();

	m_GameStates.pop_back();

	SAFE_DELETE_PTR(pGameState);

	if (m_GameStates.size() > 0 && m_ReplacementGameState == nullptr)
	{
		m_GameStates.back()->OnResume();
	}
}

void GameStateManager::PerformReplaceGameState()
{
	PushGameState(m_ReplacementGameState);
	m_ReplacementGameState = nullptr;
}

void GameStateManager::PushGameState(const GameStateCreate* pGameStateCreate)
{
	if (m_GameStates.size() > 0 && m_ReplacementGameState == nullptr)
	{
		m_GameStates.back()->OnSuspend();
	}

	GameState* pGameState = GetGameState(pGameStateCreate);

	if (pGameState)
	{
		m_GameStates.push_back(pGameState);
	}
}

void GameStateManager::PopGameState()
{
	m_bPopGameState.push_back(true);
}

void GameStateManager::ReplaceGameState(const GameStateCreate* pGameStateCreate)
{
	PopGameState();
	m_ReplacementGameState = pGameStateCreate;
}

GameStateManager* GameStateManager::Instance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new GameStateManager();
	}

	return m_pInstance;
}

void GameStateManager::AddGameObjectToCurrentGameState(GameObject* pGameObject)
{
	if (m_GameStates.size() > 0)
	{
		m_GameStates.back()->AddGameObject(pGameObject);
	}
}
/*
void GameStateManager::RegisterGameStateCreationData(int gameStateId, GameStateCreate* pGameStateCreate)
{
	if (pGameStateCreate == nullptr)
		return;

	std::map<int, GameStateCreate*>::const_iterator it = m_GameStateCreationData.find(gameStateId);
	if (it != m_GameStateCreationData.end())
	{
		return;
	}

	m_GameStateCreationData.insert({ gameStateId, pGameStateCreate });
}

GameStateCreate* GameStateManager::GetGameStateCreationData(const int gameStateId)
{
	std::map<int, GameStateCreate*>::const_iterator it = m_GameStateCreationData.find(gameStateId);
	if (it != m_GameStateCreationData.end())
	{
		return it->second;
	}

	return nullptr;
}
*/
GameState* GameStateManager::GetGameState(const GameStateCreate* pGameStateCreate)
{
	if (pGameStateCreate)
	{
		if (m_pGameStateFactory)
		{
			return m_pGameStateFactory->GetGameState(pGameStateCreate);
		}
	}

	return nullptr;
}
