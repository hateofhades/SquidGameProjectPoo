#pragma once
#include "Player.h"

using namespace std;

enum supervisorType
{
    CIRCLE,
    TRIANGLE,
    RECTANGLE,
    NONE
};

class Supervisor : public Player
{
private:
    supervisorType type;

public:
    Supervisor();
    Supervisor(string firstName, string lastName, string city, supervisorType type);
    string getSupervisorType();
    void printInfo();
};