#include <iostream>

#include "Game.h"

using namespace std;

int main()
{
    Game game;
    game.playRedLightGreenLight();
    game.playTugOfWar();
    game.playMarbles();
    game.playGenken();
    game.end();
    return 0;
}