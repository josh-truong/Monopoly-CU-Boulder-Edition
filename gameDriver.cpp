#include <iostream>
#include <iomanip>
#include "Game.h"
using namespace std;

int main()
{   
    cout << endl << endl << endl;
    cout << setw(50) << "Welcome to a Game of Monopoly!" <<endl;
    cout << setw(50) << "Theme: CU Boudler" << endl;
    cout << setw(50) << "Solgan: The only place in Boulder where you can get rich!" << endl;

    Game monopoly;
    bool successfulRead = monopoly.readPlayers();
    monopoly.readProperty();
    if(!successfulRead)
    {
        successfulRead = monopoly.readPlayers();
    }

    string playerQuit;
    int playerMenuOptions = 0;
    int quitcounter = 0;
    do
    {
        int currentTurn = monopoly.getCurrentTurn();
        int numPlayers = monopoly.getNumPlayers();
        int amountBankrupt = monopoly.getAmountofBankruptPlayers();
        if(amountBankrupt == (numPlayers - 1))
        {
            quitcounter = 1;
        }
        else if(monopoly.getBankruptStatus(currentTurn) == false && monopoly.getNumPlayers() != 1)
        {
            if(monopoly.getInJail() == true && monopoly.getTurnsInJail() > 0)
            {
                cout << "You are in jail for " << monopoly.getTurnsInJail() << " turn." << endl;
                monopoly.setTurnsInJail(monopoly.getTurnsInJail() - 1);
                monopoly.endTurn();
            }
            else
            {
                if(monopoly.getDisplayStatus() == true)
                {
                    cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
                    monopoly.roll();
                    monopoly.move();
                    monopoly.display_MapAndPlayer();
                    monopoly.checkOwnership(currentTurn);
                }
                cout << endl;
                cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
                cout << "Menu" << endl;
                cout << "1. Morgage" << endl;
                cout << "2. List of Owned Properties" << endl;
                cout << "3. Get Players Info" << endl;
                cout << "4. Balance" << endl;
                cout << "5. Get Property Info" << endl;
                cout << "6. Buy House" << endl;
                cout << "7. Trade" << endl;
                cout << "8. End Turn" << endl;
                cout << "9. Withdraw" << endl;
                cout << "10. QUIT GAME" << endl;
                cin >> playerMenuOptions;

                if(cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "\x1B[91m" << "You Entered a non-digit Input" << "\x1B[0m" << endl;
                }
                else
                {
                    switch(playerMenuOptions)
                    {
                        case 1:
                        {
                            int morgageProperty_uI;
                            monopoly.morgage();
                            break;
                        }
                        case 2:
                        {
                            monopoly.listOfOwnedProperties();
                            break;
                        }
                        case 3:
                        {
                            monopoly.listOfOwnedProperties_ByOtherPlayers();
                            break;
                        }
                        case 4:
                        {
                            monopoly.currentPlayerBal();
                            break;
                        }
                        case 5:
                        {
                            int propertyLocation;
                            cout << "Enter from 0-39: ";
                            cin >> propertyLocation;
                            monopoly.getPropertyInfo(propertyLocation);
                            break;
                        }
                        case 6: 
                        {
                            int location = monopoly.getPlayerLocation();
                            monopoly.buyHouse(location);
                            break;
                        }
                        case 7:
                        {
                            int tradeMenu;
                            cout << "-------------Trade Menu-------------" << endl;
                            cout << "1. Trade with Money" << endl;
                            cout << "2. Trade with Property" << endl;
                            cin >> tradeMenu;

                            if(tradeMenu == 1)
                            {
                                int wantedProperty;
                                int moneyDeal;
                                cout << "Which property do you want? (Enter from 0 - 39): ";
                                cin >> wantedProperty;
                                cout << "How much money do you want to trade? $";
                                cin >> moneyDeal;
                                if(wantedProperty >= 0 && wantedProperty <= 39)
                                {
                                    monopoly.tradeWithMoney(wantedProperty, moneyDeal);
                                }
                                else
                                {
                                    cout << "You entered a number outside of the range." << endl;
                                }
                            }
                            else if(tradeMenu == 2)
                            {
                                int IwantThis;
                                int IGiveYouThat;
                                cout << "Which property do you want? (Enter from 0 - 39): ";
                                cin >> IwantThis;
                                cout << "Which Property do you want to trade for property [" << IwantThis << "]? ";
                                cin >> IGiveYouThat;
                                if(IGiveYouThat >= 0 && IGiveYouThat <= 39 && IwantThis >= 0 && IwantThis <= 39)
                                {    
                                    monopoly.tradeWithProperty(IwantThis, IGiveYouThat);
                                }
                                else
                                {
                                    cout << "You entered in a value outside of the range." << endl;
                                }
                            }
                            break;
                        }
                        case 8:
                        {
                            if(monopoly.getDisplayStatus() == true)
                            {
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " --> " << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "]" << "\x1B[0m" << " You have an extra turn!"<< endl;
                            }
                            if(monopoly.getDisplayStatus() == false)
                            {
                                monopoly.setDisplayStatus(true);
                                monopoly.endTurn();
                            }              
                            break;
                        }
                        case 9:
                        {
                            int repeater = 0;
                            while(repeater == 0)
                            {
                                cout << "Are you sure you want to withdraw from the game?" << endl;
                                cout << "NOTE* That withdrawing from this game means that you will have declared bankruptcy!" << endl;
                                cout << "Enter QUIT or Enter CANCEL. Ensure the letters are completely capitalized." << endl;
                                string entry;
                                cin >> entry;
                                if(entry == "QUIT")
                                {
                                    monopoly.bankrupt();
                                    repeater = 1;
                                }
                                else if(entry == "CANCEL")
                                {
                                    cout << "The game goes on." << endl;
                                    repeater = 1;
                                }
                                else
                                {
                                    cout << "Invalid input." << endl;
                                }
                            }
                            break;
                        }
                        case 10:
                        {
                            int repeater = 0;
                            while(repeater == 0)
                            {
                                cout << "Are you sure you want to quit?" << endl;
                                cout << "NOTE* This command will stop the game completetly" << endl;
                                cout << "Enter QUIT or Enter CANCEL. Ensure the letters are completely capitalized." << endl;
                                string entry;
                                cin >> entry;
                                if(entry == "QUIT")
                                {
                                    quitcounter = 1;
                                    repeater = 1;
                                }
                                else if(entry == "CANCEL")
                                {
                                    cout << "The game goes on." << endl;
                                    repeater = 1;
                                }
                                else
                                {
                                    cout << "Invalid input." << endl;
                                }
                            }
                            break;
                        }
                        case 11:
                        {
                            int propertyLocation;
                            cout << "Enter property Location: ";
                            cin >> propertyLocation;
                            monopoly.buy(propertyLocation, 1);
                            break;
                        }
                        default:
                            cout << "You have entered an option that does not exits." << endl;
                            break;
                    }
                }
            }
        }
        else
        {
            monopoly.endTurn();
        }
    } while (quitcounter == 0);

    monopoly.endGame();
    return 0;
}