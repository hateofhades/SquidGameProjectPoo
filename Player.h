#pragma once
#include <string>

using namespace std;

class Player
{
private:
    string firstName, lastName, city;
    unsigned int debt, weight, playerNumber;

public:
    Player();
    Player(string firstName, string lastName, string city);
    string getFullName();
    string getLastName();
    string getFirstName();
    string getCity();
    unsigned int getDebt();
    unsigned int getWeight();
    unsigned int getPlayerNumber();
    void setPlayerNumber(unsigned int playerNumber);
    virtual void printInfo();
};