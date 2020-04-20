#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>

using namespace std;

int main()
{
    Game testgame;
    testgame.readPlayers();
    testgame.readProperty();
    testgame.roll();
    testgame.buy(28,2);
    testgame.waterElectricRent();
    return 0;
}