#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::communityChest()
{
    srand((unsigned)time(0));
    int result = rand() % 17 + 1;

    string line;
    string playerPiece = player[currentTurn - 1].getPlayerChar();
    vector <string> communityChestLines;
    ifstream communitychest;
    communitychest.open("communitychest.txt");
    if(communitychest.is_open())
    {
        while(getline(communitychest, line, '\r'))
        {
            communityChestLines.push_back(line);
        }
        cout << communityChestLines[result - 1] << endl;
        switch(result)
        {
            case 1:
            {
                setPiece(0,playerPiece, currentTurn);
                erase(currentTurn);
                passGo();
                display_MapAndPlayer();
                break;
            }
            case 2:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 200;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 3:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 4:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 5:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 6:
            {
                jail();
                break;
            }
            case 7:
            {
                for(int i = 0; i < numPlayers - 1; i++)
                {
                    int amount = player[currentTurn - 1].getBalance();
                    amount = amount + 50;
                    player[currentTurn - 1].setBalance(amount);
                }
                for(int j = 0; j < numPlayers; j++)
                {
                    if(currentTurn - 1 != j)
                    {
                        int amount = player[j].getBalance();
                        amount = amount - 50;
                        player[j].setBalance(amount);
                    }
                }
                break;
            }
            case 8:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 9:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 20;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 10:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 10;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 11:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 12:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 13:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 150;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 14:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 25;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 15:
            {
                string user = player[currentTurn - 1].getName();
                int counter = 0;
                for(int i = 0; i < 40; i++)
                {
                    if(user == property[i].getOwner())
                    {
                        counter += property[i].getNumBuildings();
                    }
                }
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 40 * counter;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 16:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 10;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 17:
            {
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::chance()
{
    srand((unsigned)time(0));
    int result = rand() % 16 + 1;

    string line;
    string playerPiece = player[currentTurn - 1].getPlayerChar();
    vector <string> chanceV;

    ifstream readChance;
    readChance.open("chance.txt");
    if(readChance.is_open())
    {
        while(getline(readChance, line, '\r'))
        {
            chanceV.push_back(line);
        }
        cout << chanceV[result - 1] << endl;
        switch(result)
        {
            case 1:
            {
                player[currentTurn - 1].setBoardLocation(0);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition,playerPiece, currentTurn);
                erase(currentTurn);
                passGo();
                display_MapAndPlayer();
                break;
            }
            case 2:
            {
                player[currentTurn - 1].setBoardLocation(24);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition,playerPiece, currentTurn);
                erase(currentTurn);
                if(player[currentTurn - 1].getBoardLocation() > 24)
                {
                    passGo();
                }
                string owner = property[24].getOwner();
                if(owner == "none")
                {
                    buy(24, currentTurn);
                }
                else if(owner == player[currentTurn - 1].getName())
                {
                    cout << "You already own this property." << endl;
                }
                else
                {
                    rent(24, currentTurn);
                }
                display_MapAndPlayer();
                break;
            }
            case 3:
            {
                player[currentTurn - 1].setBoardLocation(11);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition,playerPiece, currentTurn);
                erase(currentTurn);
                if(player[currentTurn - 1].getBoardLocation() > 11)
                {
                    passGo();
                }
                string owner = property[11].getOwner();
                if(owner == "none")
                {
                    buy(11, currentTurn);
                }
                else if(owner == player[currentTurn - 1].getName())
                {
                    cout << "You already own this property." << endl;
                }
                else
                {
                    rent(11, currentTurn);
                }
                display_MapAndPlayer();
                break;
            }
            case 4:
            {
                int playerposition = player[currentTurn - 1].getBoardLocation();
                if(playerposition == 7 || playerposition == 36)
                {
                    player[currentTurn - 1].setBoardLocation(12);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition,playerPiece, currentTurn);
                    erase(currentTurn);
                    string owner = property[12].getOwner();
                    if(owner == "none")
                    {
                        buy(12, currentTurn);
                    }
                    else if(owner == player[currentTurn - 1].getName())
                    {
                        cout << "You already own this property." << endl;
                    }
                    else
                    {
                        int OwnerNumber = 5;
                        for(int i = 0; i < numPlayers; i++)
                        {
                            if(property[12].getOwner() == player[i].getName())
                            {
                                OwnerNumber = i;
                            }
                        }
                        int amountlost = player[currentTurn - 1].getBalance();
                        amountlost = amountlost - 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amountlost);

                        int amountgained = player[currentTurn - 1].getBalance();
                        amountgained = amountgained + 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amountgained);
                    }
                }
                else if(playerposition == 22)
                {
                    player[currentTurn - 1].setBoardLocation(28);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition,playerPiece, currentTurn);
                    erase(currentTurn);

                    string owner = property[28].getOwner();
                    if(owner == "none")
                    {
                        buy(28, currentTurn);
                    }
                    else if(owner == player[currentTurn - 1].getName())
                    {
                        cout << "You already own this property." << endl;
                    }
                    else
                    {
                        int OwnerNumber = 5;
                        for(int i = 0; i < numPlayers; i++)
                        {
                            if(property[28].getOwner() == player[i].getName())
                            {
                                OwnerNumber = i;
                            }
                        }
                        int amountlost = player[currentTurn - 1].getBalance();
                        amountlost = amountlost - 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amountlost);

                        int amountgained = player[currentTurn - 1].getBalance();
                        amountgained = amountgained + 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amountgained);
                    }
                }
                display_MapAndPlayer();
                break;
            }
            case 5:
            {
                int playerposition = player[currentTurn - 1].getBoardLocation();
                if(playerposition == 7)
                {
                    player[currentTurn - 1].setBoardLocation(15);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition,playerPiece, currentTurn);
                    erase(currentTurn);

                    string owner = property[15].getOwner();
                    if(owner == "none")
                    {
                        buy(15, currentTurn);
                    }
                    else if(owner == player[currentTurn - 1].getName())
                    {
                        cout << "You already own this property." << endl;
                    }
                    else
                    {
                        rent(15, currentTurn);
                        rent(15, currentTurn);
                    }
                }
                else if(playerposition == 22)
                {
                    player[currentTurn - 1].setBoardLocation(25);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition,playerPiece, currentTurn);
                    erase(currentTurn);

                    string owner = property[25].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            buy(25, currentTurn);
                        }
                    }
                    else if(owner == player[currentTurn - 1].getName())
                    {
                        cout << "You already own this property." << endl;
                    }
                    else
                    {
                        rent(25, currentTurn);
                        rent(25, currentTurn);
                    }
                }
                else if(playerposition == 38)
                {
                    player[currentTurn - 1].setBoardLocation(5);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition,playerPiece, currentTurn);
                    erase(currentTurn);

                    string owner = property[5].getOwner();
                    if(owner == "none")
                    {
                        buy(5, currentTurn);
                    }
                    else if(owner == player[currentTurn - 1].getName())
                    {
                        cout << "You already own this property." << endl;
                    }
                    else
                    {
                        rent(5, currentTurn);
                        rent(5, currentTurn);
                    }
                }
                display_MapAndPlayer();
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
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 8:
            {
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation() - 3;
                setPiece(newPlayerPosition, playerPiece, currentTurn);
                erase(currentTurn);   
                string owner = property[newPlayerPosition].getOwner();    
                if(newPlayerPosition == 4)
                {
                    incomeTax();
                }      
                else if(newPlayerPosition == 33)
                {
                    communityChest();
                }   
                else if(owner == "none")
                {
                    buy(newPlayerPosition, currentTurn);
                }
                else if(owner == player[currentTurn - 1].getName())
                {
                    cout << "You already own this property." << endl;
                }
                else
                {
                    rent(newPlayerPosition, currentTurn);
                }
                display_MapAndPlayer();
                break;
            }
            case 9:
            {
                jail();
                display_MapAndPlayer();
                break;
            }
            case 10:
            {
                string user = player[currentTurn - 1].getName();
                int counter = 0;
                for(int i = 0; i < 40; i++)
                {
                    if(user == property[i].getOwner())
                    {
                        counter += property[i].getNumBuildings();
                    }
                }
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 25 * counter;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 11:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 15;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 12:
            {
                player[currentTurn - 1].setBoardLocation(5);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition,playerPiece, currentTurn);
                erase(currentTurn);
                string owner = property[5].getOwner();
                if(player[currentTurn - 1].getBoardLocation() > 5)
                {
                    passGo();
                }
                if(owner == "none")
                {
                    buy(5, currentTurn);
                }
                else if(owner == player[currentTurn - 1].getName())
                {
                    cout << "You already own this property." << endl;
                }
                else
                {
                    rent(5, currentTurn);
                }
                display_MapAndPlayer();
                break;
            }
            case 13:
            {
                player[currentTurn - 1].setBoardLocation(39);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition,playerPiece, currentTurn);
                erase(currentTurn);
                string owner = property[39].getOwner();
                if(owner == "none")
                {
                    buy(39, currentTurn);
                }
                else if(owner == player[currentTurn - 1].getName())
                {
                    cout << "You already own this property." << endl;
                }
                else if(owner == "Mr.Monopoly (Rich Uncle Pennybags)")
                {
                    cout << "This property will temporarily have no effect. Consider yourself lucky." << endl;
                }
                else
                {
                    rent(39, currentTurn);
                }
                display_MapAndPlayer();
                break;
            }
            case 14:
            {
                //Unfortunate Player
                for(int i = 0; i < numPlayers - 1; i++)
                {
                    int amount = player[currentTurn - 1].getBalance();
                    amount = amount - 50;
                    player[currentTurn - 1].setBalance(amount);
                }
                //Lucky Player
                for(int j = 0; j < numPlayers; j++)
                {
                    if(currentTurn - 1 != j)
                    {
                        int amount = player[j].getBalance();
                        amount = amount + 50;
                        player[j].setBalance(amount);
                    }
                }
                break;
            }
            case 15:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 150;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 16:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
        }
        readChance.close();
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