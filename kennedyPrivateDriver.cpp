#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>

using namespace std;

int main()
{
    Game testgame;
    testgame.readPlayers();
    testgame.passGo();
    testgame.endGame("qUiT");
    return 0;
}