#ifndef _GAME_STATE_MANAGER_H_
#define _GAME_STATE_MANAGER_H_

#include <vector>
#include <map>

class GameState;
class GameStateCreate;
class GameObject;
class ASCIIRenderer;
class GameStateFactory;

class GameStateManager
{
public:
	static GameStateManager* Instance();
	~GameStateManager();

	void Update(float delta);
	void Render(ASCIIRenderer* pRenderer);

	void PushGameState(const GameStateCreate* pGameStateCreate);
	void PopGameState();

	void ReplaceGameState(const GameStateCreate* pGameStateCreate);

	void AddGameObjectToCurrentGameState(GameObject* pGameObject);

	//void RegisterGameStateCreationData(int gameStateId, GameStateCreate* pGameStateCreate);

	void SetGameStateFactory(GameStateFactory* pGameStateFactory) { m_pGameStateFactory = pGameStateFactory; }

private:

	GameStateManager();

	void PerformPopGameState();
	void PerformReplaceGameState();

	//GameStateCreate* GetGameStateCreationData(const int gameStateId);
	GameState* GetGameState(const GameStateCreate* pGameStateCreate);

	std::vector<bool> m_bPopGameState;
	std::vector<GameState*> m_GameStates;

	static GameStateManager* m_pInstance;

	const GameStateCreate* m_ReplacementGameState;

	//std::map<int, GameStateCreate*> m_GameStateCreationData;

	GameStateFactory* m_pGameStateFactory;
	
};

#endif
