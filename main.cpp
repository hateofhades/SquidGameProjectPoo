#include <iostream>

#include "Game.h"
Game *Game::instance = nullptr;

using namespace std;

int main()
{
    Game *game = Game::getInstance();

    game->playRedLightGreenLight();
    game->playTugOfWar();
    game->playMarbles();
    game->playGenken();
    game->end();

    return 0;
}