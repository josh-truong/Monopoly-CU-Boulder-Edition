#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
using namespace std;


//PLAYER CLASS IS FINISHED
class Player
{
    private:
        int balance;
        string playerName;
        int playerPos_x;
        int playerPos_y;
        bool bankrupt;
    public:
        Player();
        
        void setName(string playerName_); // Set player name
        // NOTE: We can only set the balance and not update it(ADD/SUBTRACT)
        void setBalance(int balance_); 
        void setPlayerPos(int x, int y);
        
        //We must only use this function when we have determined that the player is bankrupted or has decided to quit
        void setBankruptStatusTrue();
        
        string getName() const; //Get player name
        int getBalance() const; //Get balance
        bool getStatus() const; // We must use this function to check if the player can play
};
#endif
