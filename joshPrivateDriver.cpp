//Note this is a public driver, if you want to test your own code, then create your own driver and call the neccessary files
//This is the brains of the program don't f*** this one up
#include <iostream>
#include "Game.h"
#include "Player.h"
using namespace std;

int main()
{
    Game monopoly;
    // bool successfulRead = monopoly.readPlayers();
    monopoly.readProperty();
    // if(!successfulRead)
    // {
    //     successfulRead = monopoly.readPlayers();
    // }
    // cout << "Welcome to a Game of Monopoly!" <<endl;
    // cout << "Theme: CU Boudler" << endl;
    // cout << "Solgan: The only place in Boulder where you can get rich!" << endl;
    // monopoly.move(0);
    // monopoly.display_MapAndPlayer();
    monopoly.getPropertyInfo(5);
    monopoly.getPropertyInfo(15);
    monopoly.getPropertyInfo(25);
    monopoly.getPropertyInfo(35);
    monopoly.getPropertyInfo(1);
    return 0;
}
