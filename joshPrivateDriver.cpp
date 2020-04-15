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
    for(int i = 1; i <= 4; i++)
    {
        cout << "Player: " << "\x1B[92m"<< monopoly.getPlayerUsername_GAME(i) << "\x1B[0m" << " turn" << endl;
        cout << "Enter " << "\x1B[91m" << "ROLL" << "\x1B[0m" << ": " << endl;
        cin >> uI;
        monopoly.roll();
        monopoly.move(i);
        monopoly.display_MapAndPlayer();
        monopoly.checkOwnership(i);
    }
    
    
    // monopoly.getPropertyInfo(2);
    // monopoly.getPropertyInfo(7);
    // monopoly.getPropertyInfo(5);
    // monopoly.getPropertyInfo(1);
    // monopoly.getPropertyInfo(0);

    // monopoly.getPropertyInfo(11);
    // monopoly.getPropertyInfo(13);
    return 0;
}
