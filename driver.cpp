//Use this to check that classes work
#include <iostream>
#include "Game.h"
#include "Player.h"
using namespace std;

int main()
{
    
    Game monopoly;
    bool successfulRead = monopoly.readPlayers();
    // monopoly.readProperty();
    if(!successfulRead)
    {
        successfulRead = monopoly.readPlayers();
    }
    cout << "Welcome to a Game of Monopoly!" <<endl;
    cout << "Theme: CU Boudler" << endl;
    cout << "Solgan: The only place in Boulder where you can get rich!" << endl;
    monopoly.move(0);
    // monopoly.getPropertyInfo(0);
    return 0;
}
