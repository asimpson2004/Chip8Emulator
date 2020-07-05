#include "GameState.h"
#include "../GameObject/GameObject.h"
#include "../GameDatabase/CreationData/GameStateCreate.h"
#include "../GameObject/GameObjectManager.h"
#include "../Renderer/ASCIIRenderer.h"

GameState::GameState(const GameStateCreate* pCreationData)
{
	if (pCreationData)
	{
		for (GDb::C_Ref<GameObjectCreate> gameObjectCreate : pCreationData->m_GameObjects)
		{
			AddGameObject(GameObjectManager::Instance()->GetGameObject(gameObjectCreate));
		}
	}

	m_Position.x = 0.0f;
	m_Position.y = 0.0f;
}

GameState::~GameState()
{
	for (std::vector<GameObject*>::iterator it = m_GameObjects.begin(); it != m_GameObjects.end(); ++it)
	{
		SAFE_DELETE_PTR(*it);
	}
}

void GameState::Update(float delta)
{
	for (unsigned int i = 0; i < m_GameObjects.size(); ++i)
	{
		m_GameObjects[i]->Update(delta);
	}
}

void GameState::Render(ASCIIRenderer* pRenderer)
{
	pRenderer->PushMatrix();

	pRenderer->Translate(m_Position);

	for (unsigned int i = 0; i < m_GameObjects.size(); ++i)
	{
		m_GameObjects[i]->Render(pRenderer);
	}

	pRenderer->PopMatrix();
}

void GameState::AddGameObject(GameObject* pGameObject)
{
	if (pGameObject)
	{
		m_GameObjects.push_back(pGameObject);
	}
}
