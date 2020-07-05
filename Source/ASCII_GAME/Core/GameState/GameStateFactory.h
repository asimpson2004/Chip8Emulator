#ifndef _GAME_STATE_FACTORY_H_
#define _GAME_STATE_FACTORY_H_

class GameState;
class GameStateCreate;

class GameStateFactory
{
public:
	virtual ~GameStateFactory() {}
	virtual GameState* GetGameState(const GameStateCreate* creationData) = 0;
};

#endif
