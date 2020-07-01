#ifndef _GAME_STATE_FACTORY_IMPL_H_
#define _GAME_STATE_FACTORY_IMPL_H_

#include "../../Core/GameState/GameStateFactory.h"

class GameStateCreate;

class GameStateFactoryImpl : public GameStateFactory
{
public:
	GameStateFactoryImpl();
	~GameStateFactoryImpl();

	virtual GameState* GetGameState(const GameStateCreate* creationData);

};

#endif
