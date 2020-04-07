#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>

using namespace std;

void luxuryTax();
{
    /*
     If the player lands on the luxury tax spot, they will have 75 dollars subtracted from their balance.
    */
    int amount = player[currentturn].getBalance();
    amount = amount - 75;
    player[currentturn].setBalance(amount);
}


int main()
{
    Game testgame;
    testgame.luxuryTax();
    cout >> player[currentturn].getBalance() >> endl;
    return 0;
}