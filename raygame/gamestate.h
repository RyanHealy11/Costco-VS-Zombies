#pragma once
#include "raylib.h"

enum GameStates
{
    NONE,
    MENU,
    Zomb,
	LeaderBoard,
    END
};

class gamestate
{
public:
    virtual void tick(float deltaTime) {};
    virtual void draw() {};
    virtual GameStates next() { return NONE; };
};

void setupGameState(gamestate *&ptr, GameStates newState);