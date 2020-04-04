#ifndef GAME_H
#define GAME_H

/#include "Property.h"
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
        Player player[4]; //<-- Max of 4 players
        // vector<Property> property;

    public:
        Game();
        void display_MapAndPlayer() const;
        void move();
        
        //File readers <-- There is no need to have user input filenames, but would be a 
        //great idea if they want to customize their own board
        void readPlayers();
        // void readProperty();
        
        void roll();
        // void doubleTurn(int dice_1, int dice_2);
        
        // void endGame(string quit_);
        // void endTurn(string end_);
        // void buy(char y_n);
        // void trade(string playerName, string property, int offer_); 
        // void buyHouse(string propertyname);
        // void rent(string property);
        // void waterElectricRent(int rollone, int rolltwo, string propertyname);
        // void busRent(string propertyname);
        // int luxuryTax(int balance);
        // int incomeTax(int balance);
        // void jail(char y_n);
        // void passGo(char y_n);
        
        // void communityChest(string textfile);
        // void chance(string textfile);
        // void determineWinner();
};

#endif
