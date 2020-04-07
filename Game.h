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
        
        //File readers <-- There is no need to have user input filenames, but would be a 
        //great idea if they want to customize their own board
        bool readPlayers();
        void readProperty();
        
        void roll();
        // void doubleTurn(int dice_1, int dice_2);
        
        void getPropertyInfo(int propertyLocation_);
        // void endGame(string quit_);
        void endTurn(string end_);
        // void buy(char y_n);
        // void trade(string playerName, string propertyoffered, int offer_, string propertywanted); 
        // void buyHouse(string propertyname);
        // void rent(string property);
        // void waterElectricRent(int rollone, int rolltwo, string propertyname);
        // void busRent(string propertyname);
        void luxuryTax();
        // void incomeTax(int balance);
        // void jail(char y_n);
        // void passGo(char y_n);
        
        // void communityChest(string textfile);
        // void chance(string textfile);
        // void determineWinner();
};

#endif
