#ifndef GAME_H
#define GAME_H

#include "Property.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Game
{
    private:
        int dice_1;
        int dice_2;
        bool inJail;
        string map[11][11][2][2];
        int numPlayers;
        int currentTurn;
        Player player[4]; //<-- Max of 4 players
        Property property[40];
        

    public:
        Game();
        void display_MapAndPlayer() const;
        void move(int currentPlayer); //Player 1,2,3,4
        void setPiece(int boardLocation, string playerPiece, int currentTurn);

        
        //File readers <-- There is no need to have user input filenames, but would be a 
        //great idea if they want to customize their own board
        bool readPlayers();
        void readProperty();

        int getNumPlayers();
        
        void roll();
        void doubleTurn(int dice_1, int dice_2); //Incomplete
        
        void getPropertyInfo(int propertyLocation_);
        void endGame(string quit_); //Incomplete
        void endTurn(string end_);
        void trade(string playerName, string propertyoffered, int offer_, string propertywanted); //Incomplete
        void buy(int propertyLocation, int currentPlayer);
        void buyHouse(int propertyLocation, int currentPlayer);// incomplete
        void rent(int propertyLocation, int currentPlayer);
        void waterElectricRent(int rollone, int rolltwo, int propertylocation); //Incomplete
        void luxuryTax();
        void incomeTax();
        void jail(); //Incomplete
        void passGo(); //Incomplete
        void morgage(int propertyLocation);
        
        void communityChest(string textfile); //Incomplete
        void chance(string textfile); //Incomplete

        string getPlayerUsername_GAME(int i);
        string getPlayerCharacter(int i);
        void checkOwnership(int currentPlayer);
        bool checkForExceptions(int boardLocation);
        void erase(int currentTurn);
        int listOfOwnedProperties();

        void banish(int currentTurn);
        
};

#endif
