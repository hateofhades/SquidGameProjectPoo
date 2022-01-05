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

template <class T>
bool isSmaller(T a, T b)
{
    return (a < b);
}

template <>
bool isSmaller(Supervisor *a, Supervisor *b)
{
    Game *game = Game::getInstance();

    return (game->getSupervisorPrize(a->getSupervisorNumber()) < game->getSupervisorPrize(b->getSupervisorNumber()));
}

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
                (*this->players[i][j]).setSupervisorNumber(supervisorNumber);
                this->supervisorPrize[supervisorNumber - 1] = -this->players[i][j]->getDebt();

                supervisorNumber++;
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

Game *Game::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Game();
    }
    return instance;
}

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

void Game::printLeftPlayers()
{
    cout << "----------------------------------------" << endl;
    cout << "Players left in the game:" << endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 3; j < 3 + this->alivePlayers[i]; j++)
        {
            cout << "Player " << (*this->players[i][j]).getPlayerNumber() << ": " << (*this->players[i][j]).getFullName() << endl;
        }
    }
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

            for (int j = i + 1; j <= 3 + this->alivePlayers[team - 1]; j++)
                (*this->players[team - 1][j - 1]) = (*this->players[team - 1][j]);

            return;
        }

    throw "Player not found!";
}

void Game::playRedLightGreenLight()
{
    cout << "First game: Red Light Green Light" << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < 3; i++)
        for (int j = 3; j < 3 + this->alivePlayers[i]; j++)
            if ((*this->players[i][j]).getPlayerNumber() % 2 == 0)
            {
                try
                {
                    this->removePlayer((*this->players[i][j]).getPlayerNumber());
                    j--;
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                    continue;
                }
            }

    cout << "----------------------------------------" << endl;
    cout << "First game has ended!" << endl
         << "----------------------------------------" << endl
         << "Left players: " << this->alivePlayers[0] + this->alivePlayers[1] + this->alivePlayers[2] << endl
         << "Total prize pool: " << this->prize << "$" << endl
         << "----------------------------------------" << endl
         << endl;
    this->printLeftPlayers();
}

void Game::playTugOfWar()
{
    cout << "Second game: Tug of War" << endl;
    cout << "----------------------------------------" << endl;

    int totalAlive = 0;
    Player *tugPlayers[this->alivePlayers[0] + this->alivePlayers[1] + this->alivePlayers[2]];

    for (int i = 0; i < 3; i++)
        for (int j = 3; j < 3 + this->alivePlayers[i]; j++)
            tugPlayers[totalAlive++] = this->players[i][j];

    Player *teams[4][totalAlive / 4];
    int teamWeights[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        cout << endl
             << "----------------------------------------" << endl;
        cout << "Team " << i + 1 << ":" << endl;
        for (int j = 0; j < totalAlive / 4; j++)
        {
            int chosen;

            do
            {
                chosen = rand() % totalAlive;
            } while (tugPlayers[chosen] == NULL);

            teams[i][j] = tugPlayers[chosen];
            teamWeights[i] += (*teams[i][j]).getWeight();
            tugPlayers[chosen] = NULL;

            cout << "Player " << (*teams[i][j]).getPlayerNumber() << ": " << (*teams[i][j]).getFullName() << endl;
        }
    }

    cout << "----------------------------------------" << endl;
    for (int i = 0; i < totalAlive; i++)
        if (tugPlayers[i] != NULL)
            cout << "Player " << (*tugPlayers[i]).getPlayerNumber() << ": " << (*tugPlayers[i]).getFullName() << " has not been assigned a team, and has advanced further!" << endl;

    cout << endl
         << "----------------------------------------" << endl;
    cout << "First game of Tug Of War" << endl
         << "Team 1 vs. Team 2" << endl;
    cout << "----------------------------------------" << endl;

    if (teamWeights[0] >= teamWeights[1])
    {
        cout << "Team 1 has won the game!" << endl;
        cout << "Team 2 has been eliminated!" << endl;

        for (int i = 0; i < totalAlive / 4; i++)
            try
            {
                this->removePlayer((*teams[1][i]).getPlayerNumber());
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                continue;
            }
    }
    else
    {
        cout << "Team 2 has won the game!" << endl;
        cout << "Team 1 has been eliminated!" << endl
             << endl;

        for (int i = 0; i < totalAlive / 4; i++)
            try
            {
                this->removePlayer((*teams[0][i]).getPlayerNumber());
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                continue;
            }
    }

    cout << "----------------------------------------" << endl;
    cout << "Second game of Tug Of War" << endl
         << "Team 3 vs. Team 4" << endl;
    cout << "----------------------------------------" << endl;

    if (teamWeights[2] >= teamWeights[3])
    {
        cout << "Team 3 has won the game!" << endl;
        cout << "Team 4 has been eliminated!" << endl;

        for (int i = 0; i < totalAlive / 4; i++)
            try
            {
                this->removePlayer((*teams[3][i]).getPlayerNumber());
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                continue;
            }
    }
    else
    {
        cout << "Team 4 has won the game!" << endl;
        cout << "Team 3 has been eliminated!" << endl
             << endl;

        for (int i = 0; i < totalAlive / 4; i++)
            try
            {
                this->removePlayer((*teams[2][i]).getPlayerNumber());
            }
            catch (const char *msg)
            {
                cout << msg << endl;
                continue;
            }
    }

    cout << "----------------------------------------" << endl;
    cout << "Second game has ended!" << endl
         << "----------------------------------------" << endl
         << "Left players: " << this->alivePlayers[0] + this->alivePlayers[1] + this->alivePlayers[2] << endl
         << "Total prize pool: " << this->prize << "$" << endl
         << "----------------------------------------" << endl
         << endl;
    this->printLeftPlayers();
}

void Game::playMarbles()
{
    cout << "Third game: Marbles" << endl;
    cout << "----------------------------------------" << endl;

    int totalMarblers = 0;
    Player *marblesPlayers[this->alivePlayers[0] + this->alivePlayers[1] + this->alivePlayers[2]];

    for (int i = 0; i < 3; i++)
        for (int j = 3; j < 3 + this->alivePlayers[i]; j++)
            marblesPlayers[totalMarblers++] = this->players[i][j];

    while (totalMarblers > 1)
    {
        int player1 = rand() % totalMarblers, player2;

        do
        {
            player2 = rand() % totalMarblers;
        } while (player1 == player2);

        int marbles1 = rand() % 6 + 1, marbles2;

        do
        {
            marbles2 = rand() % 6 + 1;
        } while (marbles2 == marbles1);

        cout << (*marblesPlayers[player1]).getFullName() << " vs." << (*marblesPlayers[player2]).getFullName() << endl;
        if (marbles1 > marbles2)
        {
            int lostNumber = (*marblesPlayers[player1]).getPlayerNumber();

            totalMarblers--;
            for (int i = player1 + 1; i <= totalMarblers; i++)
                marblesPlayers[i - 1] = marblesPlayers[i];

            if (player1 < player2)
                player2--;

            totalMarblers--;
            for (int i = player2 + 1; i <= totalMarblers; i++)
                marblesPlayers[i - 1] = marblesPlayers[i];

            try
            {
                this->removePlayer(lostNumber);
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
        }
        else
        {
            int lostNumber = (*marblesPlayers[player2]).getPlayerNumber();

            totalMarblers--;
            for (int i = player1 + 1; i <= totalMarblers; i++)
                marblesPlayers[i - 1] = marblesPlayers[i];
            totalMarblers--;

            if (player1 < player2)
                player2--;

            for (int i = player2 + 1; i <= totalMarblers; i++)
                marblesPlayers[i - 1] = marblesPlayers[i];

            try
            {
                this->removePlayer(lostNumber);
            }
            catch (const char *msg)
            {
                cout << msg << endl;
            }
        }
    }

    if (totalMarblers)
        cout << (*marblesPlayers[0]).getFullName() << " has advanced without playing." << endl;

    cout << "----------------------------------------" << endl;
    cout << "Third game has ended!" << endl
         << "----------------------------------------" << endl
         << "Left players: " << this->alivePlayers[0] + this->alivePlayers[1] + this->alivePlayers[2] << endl
         << "Total prize pool: " << this->prize << "$" << endl
         << "----------------------------------------" << endl
         << endl;
    this->printLeftPlayers();
}

void Game::playGenken()
{
    cout << "Fourth and last game: Genken" << endl;
    cout << "----------------------------------------" << endl;

    int genkens = 0;
    Player *genkenPlayers[this->alivePlayers[0] + this->alivePlayers[1] + this->alivePlayers[2]];

    for (int i = 0; i < 3; i++)
        for (int j = 3; j < 3 + this->alivePlayers[i]; j++)
            genkenPlayers[genkens++] = this->players[i][j];

    while (genkens > 1)
    {
        cout << "----------------------------------------" << endl;
        cout << (*genkenPlayers[genkens - 1]).getFullName() << " vs. " << (*genkenPlayers[genkens - 2]).getFullName() << endl;

        int player1choose, player2choose;
        do
        {
            player1choose = rand() % 3 + 1;
            player2choose = rand() % 3 + 1;

            cout << "Player 1 choose: " << (player1choose == 1 ? "Rock" : player1choose == 2 ? "Paper"
                                                                                             : "Scissors")
                 << endl;
            cout << "Player 2 choose: " << (player2choose == 1 ? "Rock" : player2choose == 2 ? "Paper"
                                                                                             : "Scissors")
                 << endl;
            if (player1choose == player2choose)
                cout << endl
                     << "Draw!" << endl
                     << endl;
        } while (player1choose == player2choose);

        if (player1choose == 1)
        {
            if (player2choose == 2)
            {
                try
                {
                    this->removePlayer((*genkenPlayers[genkens - 1]).getPlayerNumber());
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }

                genkens--;
            }
            else
            {
                int eliminatedNumber = (*genkenPlayers[genkens - 2]).getPlayerNumber();
                genkenPlayers[genkens - 2] = genkenPlayers[genkens - 1];

                try
                {
                    this->removePlayer(eliminatedNumber);
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }

                genkens--;
            }
        }
        else if (player1choose == 2)
        {
            if (player2choose == 1)
            {
                int eliminatedNumber = (*genkenPlayers[genkens - 2]).getPlayerNumber();
                genkenPlayers[genkens - 2] = genkenPlayers[genkens - 1];

                try
                {
                    this->removePlayer(eliminatedNumber);
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }

                genkens--;
            }
            else
            {
                try
                {
                    this->removePlayer((*genkenPlayers[genkens - 1]).getPlayerNumber());
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }

                genkens--;
            }
        }
        else
        {
            if (player2choose == 1)
            {
                try
                {
                    this->removePlayer((*genkenPlayers[genkens - 1]).getPlayerNumber());
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }

                genkens--;
            }
            else
            {
                int eliminatedNumber = (*genkenPlayers[genkens - 2]).getPlayerNumber();
                genkenPlayers[genkens - 2] = genkenPlayers[genkens - 1];

                try
                {
                    this->removePlayer(eliminatedNumber);
                }
                catch (const char *msg)
                {
                    cout << msg << endl;
                }

                genkens--;
            }
        }
    }

    cout << "----------------------------------------" << endl;
    cout << "Fourth and last game has ended!" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Left players: " << this->alivePlayers[0] + this->alivePlayers[1] + this->alivePlayers[2] << endl;
    cout << "Total prize pool: " << this->prize << "$" << endl;
    cout << "----------------------------------------" << endl;

    this->setWinner(genkenPlayers[0]);

    this->printLeftPlayers();
}

void Game::end()
{
    int supervisorNumberWinner = this->winner->getSupervisorNumber(), supervisorDebt;

    switch (supervisorNumberWinner)
    {
    case 1:
    case 2:
    case 3:
        supervisorDebt = this->players[0][supervisorNumberWinner - 1]->getDebt();
        break;
    case 4:
    case 5:
    case 6:
        supervisorDebt = this->players[1][supervisorNumberWinner - 4]->getDebt();
        break;
    case 7:
    case 8:
    case 9:
        supervisorDebt = this->players[2][supervisorNumberWinner - 7]->getDebt();
        break;
    }

    this->supervisorPrize[supervisorNumberWinner] += supervisorDebt * 10;

    cout << "----------------------------------------" << endl;
    cout << "This edition of the C++ Squid Game has ended!" << endl;
    cout << "----------------------------------------" << endl;
    cout << "The winner is: " << (*this->getWinner()).getFullName() << endl;
    cout << "Win ammount: " << this->prize << "$" << endl;
    cout << "----------------------------------------" << endl;

    Player *supervisors[9];
    int teamPrize[3] = {0, 0, 0};
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            supervisors[i * 3 + j] = this->players[i][j];
            teamPrize[i] += this->supervisorPrize[i * 3 + j];
        }

    for (int i = 0; i < 9; i++)
        for (int j = i + 1; j < 9; j++)
            if (isSmaller((Supervisor *)supervisors[i], (Supervisor *)supervisors[j]))
                swap(supervisors[i], supervisors[j]);

    for (int i = 0; i < 9; i++)
        cout << "Supervisor " << supervisors[i]->getSupervisorNumber() << ": " << supervisors[i]->getFullName() << " has won " << this->supervisorPrize[supervisors[i]->getSupervisorNumber() - 1] << "$" << endl;

    cout << "----------------------------------------" << endl;

    int maxPrize = teamPrize[0], maxPrizeIndex = 0;
    for (int i = 1; i < 3; i++)
        if (teamPrize[i] > maxPrize)
        {
            maxPrize = teamPrize[i];
            maxPrizeIndex = i;
        }

    cout << "Team " << maxPrizeIndex + 1 << " has won the most money: " << maxPrize << "$!" << endl;
    cout << "----------------------------------------" << endl;
}

int Game::getSupervisorPrize(int supervisorNumber)
{
    return this->supervisorPrize[supervisorNumber - 1];
}

void Game::setWinner(Player *winner)
{
    this->winner = winner;
}

Player *Game::getWinner()
{
    return this->winner;
}