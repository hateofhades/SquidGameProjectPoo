#include <iostream>
#include <stdlib.h>
#include <time.h>

#include "Player.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Player jonni("John", "Doe", "New York", true, CIRCLE);

    jonni.printInfo();

    return 0;
}