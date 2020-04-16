#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>

using namespace std;

void Game::communityChest(string textfile)
{
    srand((unsigned)time(0));
    int result = rand() % 17 + 1;
    string line;
    ifstream communitychest;
    communitychest.open(textfile);
    if(communitychest.is_open())
    {
        int counter = 1;
        while(getline(communitychest, line) && counter < result)
        {
            counter++;
        }
        switch(result)
        {
            case 1:
            {
                cout << line << endl;

                break;
            }
            case 2:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 200;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 3:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 4:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 5:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 6:
            {
                cout << line  << endl;
                jail();
                break;
            }
            case 7:
            {
                cout << line  << endl;
                break;
            }
            case 8:
            {
                cout << line  << endl;
                break;
            }
            case 9:
            {
                cout << line  << endl;
                break;
            }
            case 10:
            {
                cout << line  << endl;
                break;
            }
            case 11:
            {
                cout << line  << endl;
                break;
            }
            case 12:
            {
                cout << line  << endl;
                break;
            }
            case 13:
            {
                cout << line  << endl;
                break;
            }
            case 14:
            {
                cout << line  << endl;
                break;
            }
            case 15:
            {
                cout << line  << endl;
                break;
            }
            case 16:
            {
                cout << line  << endl;
                break;
            }
            case 17:
            {
                cout << line << endl;
                break;
            }
        }
    }
    else
    {
        cout << "Text file failed to open." << endl;
    }
    /*
    This function will read the community chest textfile, generate a random number between 1 and 17, determine what message to print
    using a getline and while loop, and apply a specific effect based on the number they obtained (these effects will be in a switch)
    */  
}

int main()
{
    Game testgame;
    testgame.chance("chance.txt");
    return 0;
}