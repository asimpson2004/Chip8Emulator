#ifndef _TEST_GAME_STATE_H_
#define _TEST_GAME_STATE_H_

#include "../../Core/GameState/GameState.h"
#include "../../Core/Utils/Utils.h"

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
	virtual void OnMessage(Message* pMessage) { UNUSED_VARIABLE(pMessage); }

private:

};

#endif
