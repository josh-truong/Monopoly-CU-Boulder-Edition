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
        int getAmountofBankruptPlayers();
        bool getInJail();
        void setInJail(bool status);
        void setTurnsInJail(int number);
        int getTurnsInJail();
        bool getDisplayStatus();
        void setDisplayStatus(int updateStatus);
        
        void roll(); //Incomplete
        
        void getPropertyInfo(int propertyLocation_);
        void endGame(); //Incomplete
        void endTurn();
        void tradeWithMoney(int propertyLocation, int deal); //Incomplete
        void tradeWithProperty(int IwantThis, int IGiveYouThat); //Incomplete
        void buy(int propertyLocation, int currentPlayer);
        void buyHouse(int propertyLocation);// incomplete
        void rent(int propertyLocation, int currentPlayer);
        void waterElectricRent(); //Incomplete
        void luxuryTax();
        void incomeTax();
        void jail(); //Incomplete
        void passGo();
        void morgage();
        void auction(int propertyLocation);
        
        void communityChest(string textfile); //Incomplete
        void chance(string textfile); //Incomplete

        string getPlayerUsername_GAME(int i);
        string getPlayerCharacter(int i);
        string toupper(string name);
        int getPlayerLocation();
        void checkOwnership(int currentPlayer);
        bool checkForExceptions(int boardLocation);
        void erase(int currentTurn);
        int listOfOwnedProperties();
        int listOfOwnedProperties_ByOtherPlayers();

        void banish(int currentTurn);
        int getCurrentTurn();
        void playerProfile();
        int biddersMenu(int currenBidderTurn);
        void bankrupt();
        int biddingPrice();

        bool getBankruptStatus(int currentTurn);
};

#endif
