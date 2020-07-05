#ifndef _CHIP_8_EMULATOR_GAME_STATE_H_
#define _CHIP_8_EMULATOR_GAME_STATE_H_

#include "../../Core/GameState/GameState.h"
#include "../../Core/Utils/Utils.h"

class GameStateCreate;
class ASCIIRenderer;

class Chip8EmulatorGameState : public GameState
{
public:

	Chip8EmulatorGameState(const GameStateCreate* pCreationData);
	~Chip8EmulatorGameState();

	virtual void Update(float delta);
	virtual void Render(ASCIIRenderer* pRenderer);
	virtual void OnSuspend();
	virtual void OnResume();

	//MessageHandler overrides
	virtual void OnMessage(Message* pMessage) { UNUSED_VARIABLE(pMessage); }

private:

};

#endif
