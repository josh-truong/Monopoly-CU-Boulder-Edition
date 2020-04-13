//Note this is a public driver, if you want to test your own code, then create your own driver and call the neccessary files
//This is the brains of the program don't f*** this one up
#include <iostream>
#include "Game.h"
#include "Player.h"
using namespace std;

int main()
{
    Game monopoly;
    bool successfulRead = monopoly.readPlayers();
    monopoly.readProperty();
    if(!successfulRead)
    {
        successfulRead = monopoly.readPlayers();
    }
    // cout << "Welcome to a Game of Monopoly!" <<endl;
    // cout << "Theme: CU Boudler" << endl;
    // cout << "Solgan: The only place in Boulder where you can get rich!" << endl;
    monopoly.roll();
    monopoly.move(1);

    monopoly.roll();
    monopoly.move(2);

    monopoly.roll();
    monopoly.move(3);

    monopoly.roll();
    monopoly.move(4);
    
    monopoly.display_MapAndPlayer();
    // monopoly.getPropertyInfo(2);
    // monopoly.getPropertyInfo(7);
    // monopoly.getPropertyInfo(5);
    // monopoly.getPropertyInfo(1);
    // monopoly.getPropertyInfo(0);

    // monopoly.getPropertyInfo(11);
    // monopoly.getPropertyInfo(13);
    return 0;
}
