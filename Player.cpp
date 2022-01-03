#include "Player.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

Player::Player()
{
    this->firstName = "Not a valid player";
    this->lastName = "Not a valid player";
    this->city = "Not a valid player";
    this->debt = 0;
    this->weight = 0;
}

Player::Player(string firstName, string lastName, string city)
{
    this->firstName = firstName;
    this->lastName = lastName;
    this->city = city;

    this->debt = rand() % 90001 + 10000;
    this->weight = rand() % 51 + 50;

    this->playerNumber = 0;
}

string Player::getFullName()
{
    return this->firstName + " " + this->lastName;
}

string Player::getLastName()
{
    return this->lastName;
}

string Player::getFirstName()
{
    return this->firstName;
}

string Player::getCity()
{
    return this->city;
}

unsigned int Player::getDebt()
{
    return this->debt;
}

unsigned int Player::getWeight()
{
    return this->weight;
}

unsigned int Player::getPlayerNumber()
{
    return this->playerNumber;
}

void Player::setPlayerNumber(unsigned int playerNumber)
{
    this->playerNumber = playerNumber;
}

void Player::printInfo()
{
    cout << "----------------------------------------" << endl;
    cout << "Player " << this->playerNumber << ": " << this->getFullName() << endl;
    cout << "City: " << this->getCity() << endl;
    cout << "Debt: " << this->getDebt() << endl;
    cout << "Weight: " << this->getWeight() << endl;
    cout << "----------------------------------------" << endl;
}