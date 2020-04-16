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

    string uI;
    do
    {
        for(int i = 1; i <= monopoly.getNumPlayers(); i++)
        {
            cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(i) << "][" << monopoly.getPlayerCharacter(i) << "] TURN" << "\x1B[0m" << endl;
            cout << "Enter " << "\x1B[91m" << "ROLL" << "\x1B[0m" << ": " << endl;
            cin >> uI;
            monopoly.roll();
            monopoly.move(i);
            monopoly.display_MapAndPlayer();
            monopoly.checkOwnership(i);
        }
    }while(uI != "Quit");
    
    return 0;
}


