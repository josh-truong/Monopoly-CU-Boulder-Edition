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

        



        cout << "\x1B[97m" << "[" << monopoly.getPlayerUsername_GAME(currentTurn) << "][" << monopoly.getPlayerCharacter(currentTurn) << "] TURN" << "\x1B[0m" << endl;
        cout << "Menu" << endl;
        cout << "1. Morgage" << endl;
        cout << "2. List of Owned Properties" << endl;
        cout << "3. Balance" << endl;
        cout << "4. Get Property Info" << endl;
        cout << "5. End Turn" << endl;
        cout << "6. QUIT" << endl;
        cin >> playerMenuOptions;



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
                cout << "Are you sure you want to quit?" << endl;
                cout << "Enter QUIT or Enter cancel: " << playerQuit << endl;

            }
            case 7:
            {
                int propertyLocation;
                cout << "Enter propertyLocation: ";
                cin >> propertyLocation;
                monopoly.buy(propertyLocation, 1);
            }
            default:
                cout << "You have entered an option that does not exits." << endl;
                break;
        }
    } while (playerQuit != "Quit");


    return 0;
}

