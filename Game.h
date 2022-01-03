#pragma once

#include "Player.h"
#include "Supervisor.h"

using namespace std;

class Game
{
private:
    Player *players[3][36];
    int alivePlayers[36];

public:
    Game();
    Player *getAlivePlayers();
    void printInfo();
    void printInfo(int team);
    void removePlayer(int playerNumber);
};