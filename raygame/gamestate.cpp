#include "gamestate.h"
// include all states .h files

#include "Zombstate.h"
#include "leaderstate.h"
#include "menustate.h"
#include "endstate.h"

#include <cassert>

void setupGameState(gamestate *&ptr, GameStates newState)
{
    switch(newState)
    {
        case GameStates::NONE:  ptr = new gamestate();  break;
        case GameStates::LeaderBoard: ptr = new leaderstate(); break;
        case GameStates::MENU:  ptr = new menustate();  break;
        case GameStates::Zomb: ptr = new Zombstate(); break;
        case GameStates::END:   ptr = new endstate();   break;
        default: assert(false && "Invalid state specified.");
    }
}