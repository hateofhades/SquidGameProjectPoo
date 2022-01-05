#pragma once

#include "Player.h"
#include "Supervisor.h"

using namespace std;

class Game
{
private:
    Player *players[3][36], *winner;
    int alivePlayers[3];
    int prize, supervisorPrize[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    Game();
    static Game *instance;

public:
    Game(Game &other) = delete;
    void operator=(const Game &) = delete;

    static Game *getInstance();

    Player *getAlivePlayers();
    void printInfo();
    void printInfo(int team);
    void printLeftPlayers();
    void removePlayer(int playerNumber);
    void playRedLightGreenLight();
    void playTugOfWar();
    void playMarbles();
    void playGenken();
    void end();
    int getSupervisorPrize(int supervisorNumber);
    Player *getWinner();
    void setWinner(Player *winner);
};