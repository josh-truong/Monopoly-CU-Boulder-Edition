#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Player.h"
using namespace std;


int main()
{
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
    bool display_status = true;
    int playerMenuOptions = 0;

    do
    {
        int currentTurn = monopoly.getCurrentTurn();

        if(display_status == true)
        {
            cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
            monopoly.roll();
            monopoly.move(currentTurn);
            monopoly.display_MapAndPlayer();
            monopoly.checkOwnership(currentTurn);
            display_status = false;
        }
        cout << endl;
        cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
        cout << "Menu" << endl;
        cout << "1. Morgage" << endl;
        cout << "2. List of Owned Properties" << endl;
        cout << "3. Balance" << endl;
        cout << "4. Get Property Info" << endl;
        cout << "5. End Turn" << endl;
        cout << "6. Trade" << endl;
        cout << "7. QUIT" << endl;
        cout << "9. Owned Properties of other players" << endl;
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
                    monopoly.playerProfile();
                    break;
                }
                case 4:
                {
                    int propertyLocation;
                    cout << "Enter from 0-39: ";
                    cin >> propertyLocation;
                    monopoly.getPropertyInfo(propertyLocation);
                    break;
                }
                case 5:
                {
                    monopoly.endTurn();
                    display_status = true;
                    break;
                }
                case 6:
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
                        monopoly.tradeWithMoney(wantedProperty, moneyDeal);
                    }
                    else if(tradeMenu == 2)
                    {
                        int IwantThis;
                        int IGiveYouThat;
                        cout << "Which property do you want? (Enter from 0 - 39): ";
                        cin >> IwantThis;
                        cout << "Which Property do you want to trade for " << IwantThis << "? ";
                        cin >> IGiveYouThat;
                        monopoly.tradeWithProperty(IwantThis, IGiveYouThat);
                    }
                    break;
                }
                case 7:
                {
                    cout << "Are you sure you want to quit?" << endl;
                    cout << "Enter QUIT or Enter cancel: " << playerQuit << endl;
                    break;
                }
                case 8:
                {
                    int propertyLocation;
                    cout << "Enter propertyLocation: ";
                    cin >> propertyLocation;
                    monopoly.buy(propertyLocation, 1);
                    break;
                }
                case 9:
                {
                    monopoly.listOfOwnedProperties_ByOtherPlayers();
                    break;
                }
                default:
                    cout << "You have entered an option that does not exits." << endl;
                    break;
            }
        }
        
    } while (playerQuit != "Quit");
    return 0;
}

// #include <iostream>
// #include <iomanip>
// #include "Game.h"
// using namespace std;


// int main()
// {
//     cout << setw(50) << "Welcome to a Game of Monopoly!" <<endl;
//     cout << setw(50) << "Theme: CU Boudler" << endl;
//     cout << setw(50) << "Solgan: The only place in Boulder where you can get rich!" << endl;

//     Game monopoly;
//     bool successfulRead = monopoly.readPlayers();
//     monopoly.readProperty();
//     if(!successfulRead)
//     {
//         successfulRead = monopoly.readPlayers();
//     }

//     string playerQuit;
//     bool display_status = true;
//     int playerMenuOptions = 0;
//     int playersAlive = 0;
//     do
//     {
//         playersAlive = 0;
//         int currentTurn = monopoly.getCurrentTurn();
        
//         for(int i = 1; i <= monopoly.getNumPlayers(); i++)
//         {
//             if(monopoly.getBankruptStatus(i) == false)
//             {
//                 playersAlive += 1;
//             }
//         }
        
//         if(monopoly.getBankruptStatus() == false && playersAlive != 1)
//         {
//             if(display_status == true)
//             {
//                 cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
//                 monopoly.roll();
//                 monopoly.move(currentTurn);
//                 monopoly.display_MapAndPlayer();
//                 monopoly.checkOwnership(currentTurn);
//                 display_status = false;
//             }
//             cout << endl;
//             cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
//             cout << "Menu" << endl;
//             cout << "1. Morgage" << endl;
//             cout << "2. List of Owned Properties" << endl;
//             cout << "3. Balance" << endl;
//             cout << "4. Get Property Info" << endl;
//             cout << "5. End Turn" << endl;
//             cout << "6. QUIT" << endl;
//             cin >> playerMenuOptions;

//             if(cin.fail())
//             {
//                 cin.clear();
//                 cin.ignore(1000, '\n');
//                 cout << "\x1B[91m" << "You Entered a non-digit Input" << "\x1B[0m" << endl;
//             }
//             else
//             {
//                 switch(playerMenuOptions)
//                 {
//                     case 1:
//                     {
//                         int morgageProperty_uI;
//                         monopoly.morgage();
//                         break;
//                     }
//                     case 2:
//                     {
//                         monopoly.listOfOwnedProperties();
//                         break;
//                     }
//                     case 3:
//                     {
//                         monopoly.playerProfile();
//                         break;
//                     }
//                     case 4:
//                     {
//                         int propertyLocation;
//                         cout << "Enter from 0-39: ";
//                         cin >> propertyLocation;
//                         monopoly.getPropertyInfo(propertyLocation);
//                         break;
//                     }
//                     case 5:
//                     {
//                         monopoly.endTurn();
//                         display_status = true;
//                         break;
//                     }
//                     case 6:
//                     {
//                         string LeaveResponse;
//                         cout << "Are you sure you want to quit?" << endl;
//                         cout << "Enter QUIT or Enter cancel: " << playerQuit << endl;
//                         cin >> LeaveResponse;
//                         if(LeaveResponse == "QUIT")
//                         {
//                             monopoly.bankrupt();
//                         }
//                         break;
//                     }
//                     case 7:
//                     {
//                         int propertyLocation;
//                         cout << "Enter propertyLocation: ";
//                         cin >> propertyLocation;
//                         monopoly.buy(propertyLocation, 1);
//                         break;
//                     }
//                     default:
//                         cout << "You have entered an option that does not exits." << endl;
//                         break;
//                 }
//             }
//         }
//         else
//         {
//             monopoly.endTurn();
//         }
        
//     } while (playersAlive != 1);
//     monopoly.endGame();
//     return 0;
// }

