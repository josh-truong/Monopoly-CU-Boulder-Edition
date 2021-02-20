#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>

using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::bankrupt()
{
    for(int i = 0; i < 40; i++)
    {
        if(player[currentTurn - 1].getName() == property[i].getOwner())
        {
            property[i].setOwner("none");
        }
    }
    player[currentTurn - 1].setBankruptStatusTrue();
    cout << "\x1B[91m" << player[currentTurn - 1].getName() << " Status is Bankrupt" << "\x1B[0m" << endl;
    int playerIsAlive = 0;
    for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getBankruptStatus() == false)
        {
            playerIsAlive++;
        }
    }

    cout << "There are " << playerIsAlive << " players left." << endl;

    srand((unsigned)time(0));
    int line;
    for(int i = 0; i < 2; i++)
    {
        line = rand() % 3 + 1;
    }

    switch(line)
    {
        case 1:
        {
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like your time has run out!" << endl;
            cout << setw(50) << "\x1B[92m" << "Blucifer has entered the game and took you as his creator (Luis Jiménez)..." << endl;
            cout << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "]" << " has left the game." << "\x1B[0m" << endl;
            break;
        }
        case 2:
        {
            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Looks like you entered an unknown realm and never returned..." << endl;
            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << player[currentTurn - 1].getName() << " has left the game.";
            break;
        }
        case 3:
        {
            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Unbeknownst to any players, you decided to go off into the mountains to live of the land and never returned." << endl;
            cout << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "] " << "\x1B[0m" << " has left the game." << endl;
            break;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::banish(int currentTurn)
{
    cout << setw(50) << "\x1B[92m" << "God has entered the game" << endl;
    cout << "\x1B[91m" << "[Mr.T & Mr.K] " << "\x1B[0m" << "Your have entered a property location that you do not own!" << endl;
    cout << "\x1B[91m" << "[Mr.T & Mr.K] " << "\x1B[0m" << "Under the 18 U.S.C § 1028. I charge you with Fraud for attempted connection with identification documents and authentication features." << endl;
    cout << "\x1B[91m" << "[Mr.T & Mr.K] " << "\x1B[0m" << "Your are herby stripped of your player rights, forgotten and banned from monopoly!" << endl;
    cout << "\x1B[91m" << toupper(player[currentTurn - 1].getName()) << "\x1B[0m" << " has left the game!" << endl;
    player[currentTurn - 1].setBankruptStatusTrue();
    for(int i = 0; i < 40; i++)
    {
        if(player[currentTurn - 1].getName() == property[i].getOwner())
        {
            property[i].setOwner("none");
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::endGame()
{
    /*
    This function will allow the users to end the game whenver they feel like it by typing in quit. This will allow for 
    the users to quit if they wish to but could also allow you to calculate the response if someone wins by setting up
    a condition to activate it in main. It print a message to a text file that will display the results and the winner, 
    along with their balances.
    */

    ofstream victory;
    victory.open("results.txt");
    int largestbalance = 0;
    string winner;
    for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getBankruptStatus() == false)
        {
            largestbalance = player[i].getBalance();
            winner = player[i].getName();
        }
    }
    victory << "The winner is " << winner << " with a balance of " << largestbalance << ". Congratulations on your monopoly." << endl;
    cout << setw(25) << "The winner is " << winner << " with a balance of $" << largestbalance << ". Congratulations on your monopoly." << endl;
}