#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "../../Core/GameState/GameState.h"

class GameStateCreate;

class MainMenuGameState : public GameState
{
public:

	MainMenuGameState(const GameStateCreate* pCreationData);
	~MainMenuGameState();

	//GameState overrides
	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnSuspend();
	virtual void OnResume();

	//MessageHandler overrides
	virtual void OnMessage(Message* pMessage);

private:

};

#endif
