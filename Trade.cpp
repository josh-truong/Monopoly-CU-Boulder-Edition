#include "Game.h"
#include <iostream>

using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::tradeWithMoney(int propertyLocation, int deal)
{
    /*
    This function allows the user to offer a trade to another player. It takes the name of the player, the property you want to offer,
    and the amount of money you want to offer. It will then allow the person being offered to decide if they want to accept the offer or not.
    If they accepted the offer, it will transfer the money and exchange the properties.
    */
   string currentOwnerOfProperty = property[propertyLocation].getOwner();
   string potentialOwner = player[currentTurn - 1].getName();
   if(currentOwnerOfProperty == "none" || currentOwnerOfProperty == "\x1B[93mMr.Monopoly (Rich Uncle Pennybags)\x1B[0m \x1B[31m \n-----THIS PROPERTY CANNOT BE OWNED!----- \x1B[0m")
   {
       cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You can't trade with a ghost." << endl;
   }
   else
   {
       //Check If potential Player Has money
       if((player[currentTurn - 1].getBalance() - deal) < 0)
       {
           cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You do not have enough money to make the deal that you just offered " << "\x1B[92m" << currentOwnerOfProperty << "\x1B[0m" << endl;
       }
       else
       {
            string currentOwnerResponse;
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like " << potentialOwner << " wants to buy your property " << "\x1B[92m" << currentOwnerOfProperty << "\x1B[0m" << endl;
            getPropertyInfo(propertyLocation);
            cout << potentialOwner << " wants to buy your property for $" << deal << endl;
            cout << "Do you accept this trade? Enter y/n" << endl;
            cin >> currentOwnerResponse;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                tradeWithMoney(propertyLocation, deal);
            }
            if(toupper(currentOwnerResponse) == "Y")
            {
                int ownerLocation;
                for(int i = 0; i < 4; i++)
                {
                    if(player[i].getName() == currentOwnerOfProperty)
                    {
                        ownerLocation = i;
                    }
                }
                int oldOwnerBalance = player[ownerLocation].getBalance();
                int newBalance = oldOwnerBalance + deal;
                player[ownerLocation].setBalance(newBalance);

                int dealersBalance = player[currentTurn - 1].getBalance();
                int difference = dealersBalance - deal;
                player[currentTurn - 1].setBalance(difference);

                property[propertyLocation].setOwner(potentialOwner);

            }
            else if(toupper(currentOwnerResponse) == "N")
            {
                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like " << currentOwnerOfProperty << " has decline your deal " << "\x1B[92m" << potentialOwner << "\x1B[0m" << endl;
            }
       }
       
   }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::tradeWithProperty(int IwantThis, int IGiveYouThat)
{
    /*
    This function allows the user to offer a trade to another player. It takes the name of the player, the property you want to offer,
    and the amount of money you want to offer. It will then allow the person being offered to decide if they want to accept the offer or not.
    If they accepted the offer, it will transfer the money and exchange the properties.
    */
   string currentOwnerOfProperty = property[IwantThis].getOwner();
   string potentialOwner = player[currentTurn - 1].getName();
   if((currentOwnerOfProperty == "none" || currentOwnerOfProperty == "\x1B[93mMr.Monopoly (Rich Uncle Pennybags)\x1B[0m \x1B[31m \n-----THIS PROPERTY CANNOT BE OWNED!----- \x1B[0m") && (0 <= IwantThis && IwantThis < 40))
   {
       cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You can't trade with a ghost." << endl;
   }
   else
   {
       //Check If potential Player Has money
       if(player[currentTurn - 1].getName() != property[IGiveYouThat].getOwner())
       {
           cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You Do Not Own " << "\x1B[92m" << property[IGiveYouThat].getPropertyName() << "\x1B[0m" << endl;
       }
       else
       {
            string currentOwnerResponse;
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like " << potentialOwner << " wants a trade with your property " << "\x1B[92m" << currentOwnerOfProperty << "\x1B[0m" << endl;
            getPropertyInfo(IwantThis);
            cout << "\x1B[92m" << potentialOwner << "\x1B[0m" << " --> " << "\x1B[92m" << currentOwnerOfProperty << "\x1B[0m" << " Will you trade your " << "\x1B[92m" << "[" << IwantThis << "] " << property[IwantThis].getPropertyName() << "\x1B[0m" << " for " << "\x1B[92m" << "[" << IGiveYouThat << "] " << property[IGiveYouThat].getPropertyName() << "\x1B[0m" << endl;
            cout << "Do you accept this trade? Enter y/n" << endl;
            cin >> currentOwnerResponse;

            if(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                tradeWithProperty(IwantThis, IGiveYouThat);
            }
            if(toupper(currentOwnerResponse) == "Y")
            {
                int ownerLocation;
                for(int i = 0; i < 4; i++)
                {
                    if(player[i].getName() == currentOwnerOfProperty)
                    {
                        ownerLocation = i;
                    }
                }
                property[IGiveYouThat].setOwner(player[ownerLocation].getName());
                property[IwantThis].setOwner(player[currentTurn - 1].getName());
            }
            else if(toupper(currentOwnerResponse) == "N")
            {
                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like " << currentOwnerOfProperty << " has decline your deal " << "\x1B[92m" << potentialOwner << "\x1B[0m" << endl;
            }
       }
       
   }
}