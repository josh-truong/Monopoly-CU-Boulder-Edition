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
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 9:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 20;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 10:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 10;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 11:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 12:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 13:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 150;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 14:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 25;
                player[currentTurn - 1].setBalance(amount);
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
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 10;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 17:
            {
                cout << line << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
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

void Game::chance(string textfile)
{
    srand((unsigned)time(0));
    int result = rand() % 16 + 1;
    string line;
    ifstream chance;
    chance.open(textfile);
    if(chance.is_open())
    {
        int counter = 1;
        while(getline(chance, line) && counter < result)
        {
            counter++;
        }
        switch(result)
        {
            case 1:
            {
                cout << line << endl;
                setPiece(0,player[currenTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 200;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 2:
            {
                cout << line  << endl;
                if(player[currentTurn - 1].getBoardLocation() > 24)
                {
                    setPiece(24, player[currenTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    int amount = player[currentTurn - 1].getBalance();
                    amount = amount + 200;
                    player[currentTurn - 1].setBalance(amount);
                }
                else
                {
                    setPiece(24, player[currenTurn - 1].getPlayerChar(), currentTurn)
                    erase(currentTurn);
                }
                break;
            }
            case 3:
            {
                cout << line  << endl;
                if(player[currentTurn - 1].getBoardLocation() > 11)
                {
                    setPiece(11, player[currenTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    int amount = player[currentTurn - 1].getBalance();
                    amount = amount + 200;
                    player[currentTurn - 1].setBalance(amount);
                }
                else
                {
                    setPiece(11, player[currenTurn - 1].getPlayerChar(), currentTurn)
                    erase(currentTurn);
                }
                break;
            }
            case 4:
            {
                cout << line  << endl;
                int playerposition = player[currentTurn - 1].getBoardLocation();
                if(playerposition == 7)
                {
                    setPiece(12, player[currenTurn - 1].getPlayerChar(), currentTurn)
                    erase(currentTurn);
                    string owner = property[12].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            cout << "Would you like to buy the property? Y for yes, N for no." << endl;
                            string answer;
                            cin >> answer;
                            if(answer == "Y")
                            {
                                buy(12, currentTurn);
                                repeater = 0;
                            }
                            else if(answer == "N")
                            {
                                repeater = 0;
                            }
                            else
                            {
                                cout << "Invalid input." << endl;
                            }
                        }
                    }
                    else
                    {
                        int amount = player[currentTurn - 1].getBalance();
                        amount = amount - 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amount);
                    }
                }
                else if(playerposition == 22)
                else if(playerposition == 38)
                break;
            }
            case 5:
            {
                cout << line  << endl;
                break;
            }
            case 6:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 7:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
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
                jail();
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
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 15;
                player[currentTurn - 1].setBalance(amount);
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
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 150;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 16:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
        }
    }
    else
    {
        cout << "Text file failed to open." << endl;
    }
    /*
    This function will read the chance textfile, generate a random number between 1 and 16, determine what message to print
    using a getline and while loop, and apply a specific effect based on the number they obtained (these effects will be in a switch)
    */  
}

int main()
{
    Game testgame;
    testgame.chance("chance.txt");
    return 0;
}