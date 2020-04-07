#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>

using namespace std;

void Game::endTurn(string end_)
{
    string endturn = toupper(end_);
    if(end_ == "END")
    {
        currentTurn = (currentTurn % 4) + 1;
        cout << "It is player " << currentTurn "'s turn." << endl;
    }
}


int main()
{
    Game test;
    string tester;
    do
    {
        cout << "Enter in end" << endl;
        cin >> tester;
        test.endTurn(tester); 
    }
    while(tester != "quit");
    return 0;
}