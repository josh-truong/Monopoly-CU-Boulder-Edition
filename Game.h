#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;

class Game
{
    private:
        int dice_1;
        int dice_2;
        bool InJail;
        char Map[44][44];
        string player[4]; //<-- Max of 4 players
        vector<string> property;

    public:
        void display_MapAndPlayer() const;
        int roll() const;
        void move() const; //<-- call the roll function
        void endGame(string quit_);
        void endTurn(string end_);
        void buy(char y_n);
        // We must figure out how to bring in the other user... We also will have to create an option for a different offer
        //Offer should include money/property
        void trade(string playerName, int property, int offer_); 
        
        
    
};

#endif
