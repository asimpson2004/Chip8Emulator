#ifndef _TEST_GAME_STATE_H_
#define _TEST_GAME_STATE_H_

#include "../../Core/GameState/GameState.h"

class GameStateCreate;

class TestGameState : public GameState
{
public:

	TestGameState(const GameStateCreate* pCreationData);
	~TestGameState();

	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnSuspend();
	virtual void OnResume();

	//MessageHandler overrides
	virtual void OnMessage(Message* pMessage) {}

private:

};

#endif
