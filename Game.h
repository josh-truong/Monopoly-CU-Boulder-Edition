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

        //Components of board
        void display_MapAndPlayer() const;
        void move(); 
        //BOARDLOCATION (0-39), STRING PLAYER PIECE (@#$%^&*)
        void setPiece(int boardLocation, string playerPiece, int currentTurn);
        void erase(int currentTurn);
        void roll();

        
        //File readers <-- There is no need to have user input filenames, but would be a 
        //great idea if they want to customize their own board
        bool readPlayers();
        void readProperty();
        //Reads an executes chance property
        void communityChest();
        void chance();

        // Player Status
        int getNumPlayers();
        int getAmountofBankruptPlayers();
        void bankrupt();
        void banish(int currentTurn);
        bool getBankruptStatus(int currentTurn);

        //End
        void endGame();
        void endTurn();

        //Jail
        void jail();
        bool getInJail();
        void setInJail(bool status);
        void setTurnsInJail(int number);
        int getTurnsInJail();
        bool getDisplayStatus();
        void setDisplayStatus(int updateStatus);
        
        
        //MENU
        void getPropertyInfo(int propertyLocation_);
        void tradeWithMoney(int propertyLocation, int deal);
        void tradeWithProperty(int IwantThis, int IGiveYouThat);
        void buy(int propertyLocation, int currentPlayer);
        void buyHouse(int propertyLocation);
        void morgage();
        int listOfOwnedProperties();
        int listOfOwnedProperties_ByOtherPlayers();
        void buyMorgaged();

        //Individual Properties
        void rent(int propertyLocation, int currentPlayer);
        void waterElectricRent(); //Incomplete
        void luxuryTax();
        void incomeTax();
        void passGo();

        //Use if no buy property
        void auction(int propertyLocation);
        int biddersMenu(int currenBidderTurn);
        int biddingPrice();

        //Player Information
        string getPlayerUsername_GAME(int i);
        string getPlayerCharacter();
        string toupper(string name);
        int getPlayerLocation();
        int getCurrentTurn();
        void currentPlayerBal();

        //Main Component
        void checkOwnership(int currentPlayer);
        bool checkForExceptions(int boardLocation);    
};

#endif
