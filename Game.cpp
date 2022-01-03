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

    int playerNumbers = 1;
    for (int i = 0; i < 3; i++)
    {
        alivePlayers[i] = 33;
        for (int j = 0; j < 36; j++)
        {
            if (j >= 3)
            {
                this->players[i][j] = new Player(firstNames[rand() % 30], lastNames[rand() % 30], cities[rand() % 30]);
                (*this->players[i][j]).setPlayerNumber(playerNumbers++);
            }
            else
                this->players[i][j] = new Supervisor(firstNames[rand() % 30], lastNames[rand() % 30], cities[rand() % 30], (supervisorType)i);
        }
    }

    cout << "Welcome to the " << rand() % 70 + 1 << "th edition of the C++ Squid Game!" << endl;
    cout << "There are " << playerNumbers - 1 << " players in the game." << endl;
    cout << "In a total of 3 teams! Each has assigned 3 supervisors and 33 players." << endl;
    cout << "Let the best win! Good luck!" << endl;
};

void Game::printInfo()
{
    for (int i = 0; i < 3; i++)
    {
        cout << "----------------------------------------" << endl;
        cout << "Team " << i + 1 << ":" << endl;
        for (int j = 0; j < 36; j++)
            (*this->players[i][j]).printInfo();

        cout << "----------------------------------------" << endl;
    }
}