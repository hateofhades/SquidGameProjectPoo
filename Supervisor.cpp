#include <iostream>
#include "Supervisor.h"

using namespace std;

string Supervisor::getSupervisorType()
{
    switch (this->type)
    {
    case CIRCLE:
        return "Circle";
    case TRIANGLE:
        return "Triangle";
    case RECTANGLE:
        return "Rectangle";
    default:
        return "None";
    }
}

Supervisor::Supervisor() : Player{}
{
    this->type = NONE;
}

Supervisor::Supervisor(string firstName, string lastName, string city, supervisorType type) : Player{firstName, lastName, city}
{
    this->type = type;
}

void Supervisor::printInfo()
{
    cout << "----------------------------------------" << endl;
    cout << "Supervisor: " << this->getFullName() << endl;
    cout << "City: " << this->getCity() << endl;
    cout << "Debt: " << this->getDebt() << endl;
    cout << "Weight: " << this->getWeight() << endl;
    cout << "Type: " << this->getSupervisorType() << endl;
    cout << "----------------------------------------" << endl;
}