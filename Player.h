#pragma once
#include <string>

using namespace std;

enum supervisorType
{
    CIRCLE,
    TRIANGLE,
    RECTTANGLE,
    NONE
};

class Player
{
private:
    string firstName, lastName, city;
    unsigned int debt, weight;
    bool isSupervisor;
    supervisorType type;

public:
    Player();
    Player(string firstName, string lastName, string city, bool isSupervisor, supervisorType type);
    string getFullName();
    string getLastName();
    string getFirstName();
    string getCity();
    unsigned int getDebt();
    unsigned int getWeight();
    bool getIsSupervisor();
    supervisorType getSupervisorType();
    void printInfo();
};