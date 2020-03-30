#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;

class Player
{
    private:
        int balance;
        string playerName;
        
    public:
        Player();
        
        string setName(string playerName_); // Set player name
        int setBalance(int balance_); //Set balance
        
        void getName() const; //Get player name
        void getBalance() const; //Get balance
};
#endif