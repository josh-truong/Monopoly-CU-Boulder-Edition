#include <iostream>
#include <iomanip>
#include "Game.h"
#include "Player.h"
using namespace std;


int main()
{

    // cout << setw(50) << "Welcome to a Game of Monopoly!" <<endl;
    // cout << setw(50) << "Theme: CU Boudler" << endl;
    // cout << setw(50) << "Solgan: The only place in Boulder where you can get rich!" << endl;


    // Game monopoly;
    // bool successfulRead = monopoly.readPlayers();
    // monopoly.readProperty();
    // if(!successfulRead)
    // {
    //     successfulRead = monopoly.readPlayers();
    // }


    // string playerQuit;
    // int playerMenuOptions = 0;
    // do
    // {
    //     int currentTurn = monopoly.getCurrentTurn();
        
    //     cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
    //     monopoly.roll();
    //     monopoly.move(currentTurn);
    //     monopoly.display_MapAndPlayer();
    //     monopoly.checkOwnership(currentTurn);

    //     cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
    //     cout << "Menu" << endl;
    //     cout << "1. Morgage" << endl;
    //     cout << "2. List of Owned Properties" << endl;
    //     cout << "3. Balance" << endl;
    //     cout << "4. End Turn" << endl;
    //     cin >> playerMenuOptions;



    //     switch(playerMenuOptions)
    //     {
    //         case 1:
    //         {
    //             int morgageProperty_uI;
    //             monopoly.morgage();
    //             break;
    //         }
    //         case 2:
    //         {
    //             monopoly.listOfOwnedProperties();
    //             break;
    //         }
    //         case 3:
    //         {
                
    //         }
    //         case 4:
    //         {
    //             monopoly.endTurn();
    //             break;
    //         }
    //         default:
    //             cout << "You have entered an option that does not exits." << endl;
    //     }

    // } while (playerQuit != "Quit");
    

    

    return 0;
}


