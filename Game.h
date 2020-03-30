#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

class Game
{
    private:
        int FirstDiceRoll
        int SecondDiceRoll
        bool InJail;
        char Map[44][44];
        string player[4]; //<-- Max of 4 players
        vector<string> property;

    public:
        void display_MapAndPlayer() const;
        int roll() const;
        void move();
    
};

#endif