#ifndef _GAME_H_
#define _GAME_H

class GameStateManager;
class ASCIIRenderer;

class Game
{
public:
	Game();
	~Game();

	void Initialise();
	void Run();

private:

	void InitialiseRenderer();
	void Update(float delta);
	void Render();

	bool m_bInitialised;
	bool m_bExitApp;
	float m_deltaTime;

	ASCIIRenderer* m_pRenderer;
	GameStateManager* m_pGameStateManager;

};


#endif
