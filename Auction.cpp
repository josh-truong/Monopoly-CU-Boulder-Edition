#include "Game.h"
#include <iostream>
#include <string>

using namespace std; 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::biddersMenu(int currenBidderTurn)
{
    int chosenOption = 0;
    cout << "\x1B[92m" << "[" << player[currenBidderTurn].getName() << "] " << "\x1B[0m" << "Turn" << endl;
    cout << "------------Bidding Menu------------" << endl;
    cout << "1. Bid" << endl;
    cout << "2. Morgage" << endl;
    cout << "3. Balance" << endl;
    cout << "4. Owned Properties" << endl;
    cout << "5. Withdraw From Bid" << endl;
    cin >> chosenOption;

    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\x1B[91m" << "You've Entered a non-digit Input" << "\x1B[0m" << endl;
        biddersMenu(currenBidderTurn);
    }
    return chosenOption;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::biddingPrice()
{
    int bidPrice = 0;
    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "How much would you like to bid? $";
    cin >> bidPrice;

    if(cin.fail())
    {
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "The input you've entered is INVALID" << endl;
        biddingPrice();
    }
    return bidPrice;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::auction(int propertyLocation)
{
    cout << "######################################################### AUCTION GROUND ##############################################################" << endl;
    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Do I have a bid?" << endl;
    getPropertyInfo(propertyLocation);
    int numBidders = numPlayers;
    bool playerBidStatus[4];
    int playerCurrentBid[4];
    

    //Initialize Array
    for(int i = 0; i < numBidders; i++)
    {
        playerBidStatus[i] = true;
        playerCurrentBid[i] = 0;
    }

    while(numBidders != 1)
    {
        for(int i = 0; (1 != numBidders) && (i < numPlayers); i++)
        {
            if(player[i].getBankruptStatus() == false && playerBidStatus[i] == true)
            {
                int repeater = 0;
                while(repeater == 0)
                {
                    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Does Player [" << player[i].getName() << "] want to bid?" << endl;
                    int biddersMenuOption = biddersMenu(i);
                    switch(biddersMenuOption)
                    {
                        case 1:
                        {
                            int bidPrice = 0;
                            bidPrice = biddingPrice();

                            int highestBid = 0;
                            for(int j = 0; j < numBidders; j++)
                            {
                                if(playerCurrentBid[j] > highestBid)
                                {
                                    highestBid = playerCurrentBid[j];
                                }
                            }

                            //Checks if the bid price is not negative and if the bid price is higher than the previous
                            while(highestBid >= bidPrice || bidPrice <= 0)
                            {
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Player " << player[i].getName() << " your bid is too low!" << endl;
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Our highest bid is currently " << "\x1B[92m" << "$" << highestBid << "\x1B[0m" << endl << endl;
                                biddersMenuOption = biddersMenu(i);
                                bidPrice = biddingPrice();
                            }
                            playerCurrentBid[i] = bidPrice;

                            // Checks player balance if they have the money to buy a property with their bid price. 
                            string morgageResponse;
                            while((player[i].getBalance() - bidPrice) < 0 && playerBidStatus[i])
                            {
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "You're bidding price is higher than your balance!" << endl;
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Would you like to morgage some of your properties? Enter y/n" << endl;
                                cin >> morgageResponse;
                                
                                if(toupper(morgageResponse) == "Y")
                                {
                                    int savedCurrentTurn = currentTurn;
                                    currentTurn = i + 1;
                                    morgage();
                                    currentTurn = savedCurrentTurn;
                                    biddersMenuOption = biddersMenu(i);
                                    bidPrice = biddingPrice();
                                    playerCurrentBid[i] = bidPrice;
                                }
                                else
                                {
                                    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << player[i].getName() << " has withdrawn from the bidding ground." << endl;
                                    playerBidStatus[i] = false;
                                    numBidders--;
                                }
                            }

                            if (playerBidStatus[0] && i == 0)
                            {
                                playerCurrentBid[0] = bidPrice;
                                cout << "Player " << "\x1B[92m" << "[" << player[i].getName() << "] " << "\x1B[0m" << "has bid for " << "\x1B[92m" << "$" << bidPrice << endl << endl;
                            }
                            if (playerBidStatus[1] && i == 1)
                            {
                                playerCurrentBid[1] = bidPrice;
                                cout << "Player " << "\x1B[92m" << "[" << player[i].getName() << "] " << "\x1B[0m" << "has bid for " << "\x1B[92m" << "$" << bidPrice << endl;
                            }
                            if (playerBidStatus[2] && i == 2)
                            {
                                playerCurrentBid[2] = bidPrice;
                                cout << "Player " << "\x1B[92m" << "[" << player[i].getName() << "] " << "\x1B[0m" << "has bid for " << "\x1B[92m" << "$" << bidPrice << endl;
                            }
                            if (playerBidStatus[3] && i == 3)
                            {
                                playerCurrentBid[3] = bidPrice;
                                cout << "Player " << "\x1B[92m" << "[" << player[i].getName() << "] " << "\x1B[0m" << "has bid for " << "\x1B[92m" << "$" << bidPrice << endl;
                            }
                            
                            repeater = 1;
                            break;
                        }
                        case 2:
                        {
                            morgage();
                            break;
                        }
                        case 3:
                        {
                            cout << "Current Balance: " << "\x1B[92m" << "$" << player[i].getBalance() << "\x1B[0m" << endl;
                            break;
                        }
                        case 4:
                        {
                            listOfOwnedProperties();
                            break;
                        }
                        case 5:
                        {
                            //Need to find player with the higher bid
                            int highestBid = 0;
                            int playerWithHighestBid;
                            for(int j = 0; j < numPlayers; j++)
                            {
                                if(playerCurrentBid[j] > highestBid && playerBidStatus[j] == true)
                                {
                                    highestBid = playerCurrentBid[j];
                                    playerWithHighestBid = j;
                                }
                            }
                            if(playerWithHighestBid == i)
                            {
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << player[i].getName() << " you are not allowed to leave the auction ground because you are our highest bidder!" << endl;
                            }
                            else
                            {
                                playerBidStatus[i] = false;
                                numBidders--;
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << player[i].getName() << " has withdrawn!" << endl;
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "There are " << numBidders << " left!" << endl;
                                repeater = 1;
                            }
                            break;
                        }
                        default:
                            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "You've Entered an Invalid Option." << endl;
                            break;
                    }
                }
            }
            int numBiddersCheck = numPlayers;
            if(numBidders == 1)
            {
                int winner;
                for(int k = 0; k < numBiddersCheck; k++)
                {   
                    if(playerBidStatus[k] == true)
                    {
                        winner = k;
                    }
                }
                cout << endl;
                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Congratulations, " << player[winner].getName() << "! You're the proud owner of " << property[propertyLocation].getPropertyName() << endl;
                property[propertyLocation].setOwner(player[winner].getName());
                int winnerBalance = player[winner].getBalance();
                cout << "Transaction: " << "\x1B[92m" << "$" << winnerBalance << "\x1B[97m" << " - $" << playerCurrentBid[winner] << endl;
                player[winner].setBalance(winnerBalance - playerCurrentBid[winner]);
                cout << "Current Balance: " << "\x1B[92m" << "$" << player[winner].getBalance() << "\x1B[0m" << endl;
            }
            
        }
    }
}