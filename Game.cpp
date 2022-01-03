#include "Game.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>

using namespace std;

string firstNames[30] = {"Savanna", "Blake", "Linda", "John", "Bob", "Richard", "Emily", "Wim", "Kenzo", "Natalie",
                         "Karen", "Sophia", "Logan", "Kylie", "Mia", "Liam", "Ava", "Olivia", "Aiden", "Emma", "Lucas",
                         "Abigail", "Noah", "Isabella", "Mason", "Aria", "Kaden", "Kapil", "Theophila", "Rajani"};

string lastNames[30] = {"Samson", "Loretta", "Baker", "Smith", "Jones", "Williams", "Brown", "Davis", "Miller", "Wilson",
                        "Moore", "Taylor", "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Thompson",
                        "Garcia", "Martinez", "Robinson", "Clark", "Rodriguez", "Lewis", "Lee", "Walker", "Hall", "Allen", "Young"};
string cities[30] = {"New York", "Bucharest", "London", "Paris", "Berlin", "Madrid", "Rome", "Barcelona", "Athens", "Sofia",
                     "Moscow", "Beijing", "Tokyo", "Seoul", "Hong Kong", "Bangkok", "Singapore", "Dubai", "Cairo", "Kuala Lumpur",
                     "New Delhi", "Delhi", "Mumbai", "Jaipur", "Surat", "Lucknow", "Mangalore", "Ahmedabad", "Jaipur", "Bhopal"};

Game::Game()
{
    srand(time(NULL));
    this->prize = 0;

    int playerNumbers = 1;
    int assignedSupervisor = 0;
    int supervisorNumber = 1;
    for (int i = 0; i < 3; i++)
    {
        alivePlayers[i] = 33;
        for (int j = 0; j < 36; j++)
        {
            if ((j - 3) % 11 == 0)
            {
                assignedSupervisor++;
            }

            if (j >= 3)
            {
                this->players[i][j] = new Player(firstNames[rand() % 30], lastNames[rand() % 30], cities[rand() % 30]);
                (*this->players[i][j]).setPlayerNumber(playerNumbers++);
                (*this->players[i][j]).setSupervisorNumber(assignedSupervisor);
            }
            else
            {
                this->players[i][j] = new Supervisor(firstNames[rand() % 30], lastNames[rand() % 30], cities[rand() % 30], (supervisorType)i);
                (*this->players[i][j]).setSupervisorNumber(supervisorNumber++);
            }
        }
    }

    cout << "Welcome to the " << rand() % 70 + 1 << "th edition of the C++ Squid Game!" << endl;
    cout << "There are " << playerNumbers - 1 << " players in the game." << endl;
    cout << "In a total of 3 teams! Each has assigned 3 supervisors and 33 players." << endl;
    cout << "Let the best win! Good luck!" << endl
         << endl
         << endl;
};

void Game::printInfo()
{
    for (int i = 0; i < 3; i++)
    {
        cout << "----------------------------------------" << endl;
        cout << "Team " << i + 1 << ":" << endl;
        for (int j = 0; j < 3 + this->alivePlayers[i]; j++)
            (*this->players[i][j]).printInfo();

        cout << "----------------------------------------" << endl;
    }
}

void Game::printInfo(int team)
{
    if (team <= 0 || team > 3)
    {
        cout << "Invalid team number!" << endl;
        return;
    }

    cout << "----------------------------------------" << endl;
    cout << "Team " << team << ":" << endl;
    for (int j = 0; j < 3 + this->alivePlayers[team - 1]; j++)
        (*this->players[team - 1][j]).printInfo();

    cout << "----------------------------------------" << endl;
}

void Game::removePlayer(int playerNumber)
{
    int team;
    if (playerNumber >= 1 && playerNumber <= 33)
        team = 1;
    else if (playerNumber >= 34 && playerNumber <= 66)
        team = 2;
    else
        team = 3;

    for (int i = 3; i < 3 + this->alivePlayers[team - 1]; i++)
        if ((int)(*this->players[team - 1][i]).getPlayerNumber() == playerNumber)
        {
            cout << "Player " << playerNumber << ":  " << (*this->players[team - 1][i]).getFullName() << " has been eliminated!" << endl;

            this->prize += (*this->players[team - 1][i]).getDebt();
            cout << (*this->players[team - 1][i]).getDebt() << "$ has been added to the prize pool. Total prize pool: " << this->prize << "$" << endl;
            this->alivePlayers[team - 1]--;

            int supervisorNumber = (*this->players[team - 1][i]).getSupervisorNumber();
            this->supervisorPrize[supervisorNumber - 1] += (*this->players[team - 1][i]).getDebt();
            cout << (*this->players[team - 1][i]).getDebt() << "$ has been added to the supervisor prize pool for supervisor number " << supervisorNumber << ": " << (*this->players[team - 1][supervisorNumber / (team * 3) - 1]).getFullName() << "." << endl;

            for (int j = i + 1; j <= 3 + this->alivePlayers[team - 1]; j++)
                (*this->players[team - 1][j - 1]) = (*this->players[team - 1][j]);
            break;
        }
}