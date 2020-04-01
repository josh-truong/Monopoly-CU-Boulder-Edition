#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <string>
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
        Game();
        void display_MapAndPlayer() const;
        int roll() const;
        void move(int rollone, int rolltwo); //<-- call the roll function
        void endGame(string quit_);
        void endTurn(string end_);
        void buy(char y_n);
        void trade(string playerName, string property, int offer_); 
        void buyhouse(string propertyname);
        void rent(string property);
        void waterelectricrent(int rollone, int rolltwo, string propertyname);
        void busrent(string propertyname);
        int luxurytax(int balance);
        int incometax(int balance);
        void jail(char y_n);
        void doubleturn(int rollone, int rolltwo);
        void passgo(char y_n);
        void communitychest(string textfile);
        void chance(string textfile);
        void determinewinner();
};

#endif