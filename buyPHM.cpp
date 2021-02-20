//buyPHM.cpp --> buy property/house/morgage
#include "Game.h"
#include <iostream>
#include <iomanip>

using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::buy(int propertyLocation, int currentPlayer)
{
    /*
    This allows players to buy properties that they have landed on if there is no ownership
    */
    string playerResponse;
    string morgagePropertyResponse = "Y";
    int playerBalance = player[currentPlayer - 1].getBalance();
    int propertyPrice = property[propertyLocation].getPropertyCost();

    //Subtract player balance
    int difference = playerBalance - propertyPrice;
    getPropertyInfo(propertyLocation);
    cout << setw(113)<< "-------------------Order Summary-------------------" << endl;
    cout << setw(100) << "Current Balance: " << "\x1B[92m" << "$" << playerBalance << endl;
    cout << setw(100) << "Balance Preview: " << "\x1B[92m" << "$" << playerBalance << "\x1B[97m" << " - $" << propertyPrice << "\x1B[0m" << endl;
    cout << setw(100) << "Expected Balance after Transaction: " << "\x1B[92m" << "$" << difference << "\x1B[0m" << endl;
    if(difference < 0)
    {
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " I'm sorry looks like your wallet is empty." << endl;
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Would you like to morgage some of your property? Enter y/n" << endl;
        cin >> morgagePropertyResponse;
        if(toupper(morgagePropertyResponse) == "Y")
        {
            morgage();
        }
        
    }
    if(property[propertyLocation].getOwner() == "none" && toupper(morgagePropertyResponse) == "Y" && difference >= 0)
    {
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " --> " << "\x1B[92m" << "[" << player[currentPlayer - 1].getName() << "]" << "\x1B[0m" << " Would you like to buy this property? Enter y/n" << endl;
        cin >> playerResponse;
        
        if(toupper(playerResponse) == "Y")
        {
            //update player balance
            property[propertyLocation].setOwner(player[currentPlayer - 1].getName());
            player[currentPlayer - 1].setBalance(difference);
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Congratulations, " << property[propertyLocation].getOwner() << "! You're the proud owner of " << property[propertyLocation].getPropertyName() << "." << endl;
            
            //Check for number of owned transport properties
            int numTransportsOwned = 0;
            for(int i = 5; i < 39; i += 10)
            {
                if(property[i].getOwner() == player[currentTurn - 1].getName() && property[i].getOwner() != "none")
                {
                    numTransportsOwned++;
                    // cout << property[j].getOwner() << " == " << player[i].getName() << " && " << property[j].getOwner() << " != none" << endl;
                    if(numTransportsOwned != 0)
                    {
                        for(int j = 5; j < 39; j += 10)
                        {
                            if(property[j].getOwner() == player[currentTurn - 1].getName() && property[j].getOwner() != "none")
                            {
                                property[j].setNumBuildings(numTransportsOwned - 1);
                            }
                        }
                    }
                }
            }
        }
        else if(toupper(playerResponse) == "N")
        {
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " I'm sorry to hear that." << endl;
            //WARNING -- We need to create and call an auction property
            auction(propertyLocation);
        }
        else
        {
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " I'm sorry, looks like you responded incorrectly. Type " << "\x1B[93m" << "y" << "\x1B[0m" << " for yes and " << "\x1B[92m" << "n" << "\x1B[0m" << " for no." << endl;
            buy(propertyLocation, currentPlayer);
        }
    }
    else if (toupper(morgagePropertyResponse) == "N")
    {
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " I'm sorry to hear that." << endl;
        auction(propertyLocation);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::buyHouse(int propertyLocation)
{
    /*
    This function will allow the user to buy a house for one of their properties. It will obtain the house cost from the property
    array and move the rent array down one position. It will also subtract the house cost from the player's balance.
    */
   
   if(!(0 <= propertyLocation && propertyLocation < 40))
   {
       cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You need to enter a property location that is within the range from 0 to 39" << endl; 
   }
   else if(property[propertyLocation].getNumBuildings() == 5)
   {
       cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You can't build any more buildings on this property!" << endl; 
   }
   else
   {
       if(property[propertyLocation].getOwner() != player[currentTurn - 1].getName())
       {
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You are not the owner of this property!" << endl; 
       }
       else
       {
            vector<int> monopolizedProperty;
            bool is_There_monopoly = false;
            for(int i = 0; i < 40; i++)
            {
                switch(propertyLocation)
                {
                    //Cannot Build
                        case 0: case 2: case 4: case 5: case 7: case 10: case 12: case 15: case 17:
                        case 20: case 22: case 25: case 28: case 30: case 33: case 35: case 36: case 38:
                        {
                            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " I'm sorry, you can't build a house here." << "\x1B[0m" << endl; 
                            i = 40;
                            break;
                        }
                        //Can Build
                        case 1: case 3: case 37: case 39: //Only need to monopolize 2 properties
                        {
                            if(player[currentTurn - 1].getName() == property[i].getOwner() && property[i].getColor() == property[propertyLocation].getColor() && property[i].getMorgage_Status() != true)
                            {
                                monopolizedProperty.push_back(i);
                            }
                            if(monopolizedProperty.size() == 2)
                            {
                                i = 40;
                                is_There_monopoly = true;
                            }
                            break;
                        }
                        case 6: case 8: case 9: case 11: case 13: case 14: case 16: case 18: case 19: case 21: //Only need to monopolize 3 properties
                        case 23: case 24: case 26: case 27: case 29: case 31: case 32: case 34: 
                        {
                            if(player[currentTurn - 1].getName() == property[i].getOwner() && property[i].getColor() == property[propertyLocation].getColor() && property[i].getMorgage_Status() != true)
                            {
                                monopolizedProperty.push_back(i);
                            }
                            if(monopolizedProperty.size() == 3)
                            {
                                i = 40;
                                is_There_monopoly = true;
                            }
                            break;
                        }
                        default:
                        {
                            cout << "Error at buildHouses" << endl;
                        }
                }
            }
            if(is_There_monopoly == true)
            {
                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You monopolized all the properties with the color " << toupper(property[propertyLocation].getColor()) << "\x1B[0m" << endl; 
                for(int i = 0; i < monopolizedProperty.size(); i++)
                {
                    int j = monopolizedProperty[i];
                    string propertyName = property[j].getPropertyName();
                    int numBuildings = property[j].getNumBuildings();
                    int propertyRent = property[j].getRent();
                    cout << "\x1B[92m" << "[" << j << "] " << propertyName << "\x1B[0m" << " | Buildings Built: " << numBuildings <<  " | Current Rent: \x1B[91m$" << propertyRent << "\x1B[0m" << endl;
                }

                int repeater = 0;
                do
                {
                    string buildResponse;
                    cout << endl;
                    cout << "----------------------------" << "\x1B[92m" << "ESTIMATION" << "\x1B[0m" << "----------------------------" << endl;
                    cout << "Current Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance()  << "\x1B[0m" << endl;
                    for(int i = 0; i < 6; i++)
                    {
                        if(i != 0)
                        {
                            cout << "[" << i << "] Building Cost " << "\x1B[92m" << "$" << property[propertyLocation].getBuildingCost() * i << "     " << "\x1B[0m";
                        }
                    }
                    cout << endl << endl;
                    cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Are you sure you want to add some buildings to your property? Enter y/n" << endl;
                    cin >> buildResponse;
                    if(toupper(buildResponse) == "Y")
                    {
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Which property do you want to build some houses on?" << endl;
                        cout << "Enter Property ";
                        for(int i = 0; i < monopolizedProperty.size(); i++)
                        {
                            if((i > 0) && property[monopolizedProperty[i]].getNumBuildings() != 5)
                            {
                                cout << " ";
                            }
                            if(property[monopolizedProperty[i]].getNumBuildings() != 5)
                            {
                                cout << monopolizedProperty[i];
                            }
                        }
                        cout << ": ";
                        int buildOnProperty;
                        cin >> buildOnProperty;
                        bool validate = false;
                        for(int i = 0; i < monopolizedProperty.size(); i++)
                        {
                            if(monopolizedProperty[i] == buildOnProperty)
                            {
                                validate = true;
                            }
                        }
                        if(validate)
                        {
                            cout << "----------------------------" << "\x1B[92m" << "Expected Rent Cost" << "\x1B[0m" << "----------------------------" << endl;
                            for(int i = 0; i < 6; i++)
                            {
                                if(i != 0)
                                {
                                    cout << "[" << i << "] Rent Cost " << "\x1B[92m" << "$" << property[buildOnProperty].getRentAt(i) << "     " << "\x1B[0m";
                                }
                            }
                            cout << endl << endl;
                            int buildMenuRepeater = 0;
                            int iWouldLikeToBuild;
                            do
                            {
                                cout << "------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You can build up to " << 5 - property[buildOnProperty].getNumBuildings() << " more buildings." << endl;
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " How many houses would you like to build? ";
                                cin >> iWouldLikeToBuild;
                                if((iWouldLikeToBuild <= (5 - property[buildOnProperty].getNumBuildings()))  //Checks if the player has enough money to buy these buildings
                                    && (player[currentTurn - 1].getBalance() - ((property[buildOnProperty].getBuildingCost() * iWouldLikeToBuild)) >= 0))
                                {
                                        bool goodToGo = false;
                                        int totalNumBuildings = property[buildOnProperty].getNumBuildings() + iWouldLikeToBuild;
                                        if(totalNumBuildings == 5)
                                        {
                                            cout << endl;
                                            for(int k = 0; k < monopolizedProperty.size(); k++)
                                            {
                                                if(property[monopolizedProperty[k]].getNumBuildings() >= 4) //Checks if player has 4 houses built on each property
                                                {
                                                    goodToGo = true;
                                                }
                                                else
                                                {
                                                    string propertyName = property[monopolizedProperty[k]].getPropertyName();
                                                    int numBuildingsOnProperty = property[monopolizedProperty[k]].getNumBuildings();
                                                    cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You have " << numBuildingsOnProperty << " buildings on property " << "[" << monopolizedProperty[k] << "] "  << propertyName << endl;
                                                    buildMenuRepeater = 1;
                                                    goodToGo = false;
                                                }
                                            }
                                            if(!goodToGo)
                                            {
                                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You need 4 houses on each property! Before you can build a hotel." << endl;
                                            }
                                            else
                                            {
                                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " UPDATE: Congrats on building your hotel!" << endl;
                                            }
                                        }
                                        else if(totalNumBuildings <= 4)
                                        {
                                            goodToGo = true;
                                            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Congratulations! You now have " << totalNumBuildings << " buildings on " << property[buildOnProperty].getPropertyName() << endl;
                                        }

                                        int propertyCurrentNumBuidlings = property[buildOnProperty].getNumBuildings();
                                        if(goodToGo)
                                        {
                                            int playerBal = player[currentTurn - 1].getBalance();
                                            int buildingCost = property[buildOnProperty].getBuildingCost();
                                            
                                            cout << "Transaction Process: " << "\x1B[92m" << "$" << playerBal << "\x1B[97m" << " - $" << buildingCost * iWouldLikeToBuild << "\x1B[0m" << endl;
                                            int difference = playerBal - (buildingCost * iWouldLikeToBuild);
                                            player[currentTurn - 1].setBalance(difference);
                                            cout << "Current Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() << endl;
                                            
                                            property[buildOnProperty].setNumBuildings(propertyCurrentNumBuidlings + iWouldLikeToBuild);
                                            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Congrats on upgrading your property!" << endl;
                                            cout << "[" << property[buildOnProperty].getPropertyLocation() << "] " << property[buildOnProperty].getPropertyName() << " Current Rent Cost: " << "\x1B[92m" << "$" << property[buildOnProperty].getRent() << "\x1B[0m" << endl;
                                            buildMenuRepeater = 1;
                                        }
                                }
                                else if(!(iWouldLikeToBuild <= (5 - property[buildOnProperty].getNumBuildings())))
                                {
                                    cout << endl;
                                    cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " That's too many buildings! " << endl;
                                }
                                else if(!(player[currentTurn - 1].getBalance() - ((property[buildOnProperty].getBuildingCost() * iWouldLikeToBuild)) >= 0))
                                {
                                    cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like you don't have enough money to buy " << iWouldLikeToBuild << " buildings." << endl;
                                    buildMenuRepeater = 1;
                                }
                            } while (buildMenuRepeater == 0);
                        }
                        else if(!(property[monopolizedProperty[buildOnProperty]].getNumBuildings() != 5))
                        {
                            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You can't build any more buildings on this property!" << endl;
                        }
                        else
                        {
                            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You are not the owner of this property!" << endl; 
                        }
                        repeater = 1;
                    }
                    else if(toupper(buildResponse) == "N")
                    {
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " There's always another time to upgrade your properties." << endl;
                        repeater = 1;
                    }
                    else
                    {
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " I'm sorry that's an INVAILD INPUT." << endl;
                    }
                }while(repeater == 0);
            }
            else
            {
                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like you haven't monopolized all the properties with the color " << toupper(property[propertyLocation].getColor()) << "!" << endl;
            }
       }
   }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::buyMorgaged()
{
    bool is_There_morgage = false;
    for(int i = 0; i < 40; i++)
    {
        if(property[i].getMorgage_Status() == true && (property[i].getOwner() == player[currentTurn - 1].getName()))
        {
            is_There_morgage = true;
        }
    }

    if(is_There_morgage)
    {
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Here's a list of your morgaged Properties." << endl;
        for(int i = 0; i < 40; i++)
        {
            if(property[i].getMorgage_Status() == true && (property[i].getOwner() == player[currentTurn - 1].getName()))
            {
                int morgagedPrice = property[i].getPropertyCost() / 2;
                int buyBackCost = morgagedPrice + (morgagedPrice * 0.1);
                cout << "\x1B[92m" << "[" << i << "] " << property[i].getPropertyName() << "\x1B[0m" << " | UNMORGAGED COST: " << "\x1B[92m" << "$" << buyBackCost << "\x1B[0m" << endl;
            }
        }
        cout << "Current Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() << "\x1B[0m" << endl;
        cout << endl;
        int unmorgageResponse;
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Which Property would you like to unmorgage? ";
        cin >> unmorgageResponse;
        if(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "INVALID INPUT" << endl;
        }
        else
        {
            bool is_Owner = false;
            for(int i = 0; i < 40; i++)
            {
                if(property[unmorgageResponse].getOwner() == player[currentTurn - 1].getName() && property[unmorgageResponse].getMorgage_Status() == true)
                {
                    is_Owner = true;
                }
            }
            if(is_Owner)
            {
                string confirmation;
                int morgagedPrice = property[unmorgageResponse].getPropertyCost() / 2;
                int buyBackCost = morgagedPrice + (morgagedPrice * 0.1);
                
                cout << "Transaction Process: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() << "\x1B[0m" << "\x1B[97m" << " - " << buyBackCost << "\x1B[0m" << endl;
                cout << "Expected Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() - buyBackCost << "\x1B[0m" << endl;
                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Would you like to buy [" << unmorgageResponse << "] " << property[unmorgageResponse].getPropertyName() << " for " << "\x1B[92m" << "$" << buyBackCost << "\x1B[0m" << endl;
                cout << "Enter yes or no: ";
                cin >> confirmation;
                if(cin.fail())
                {
                    cout << "INVALID INPUT" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
                else
                {
                    if(toupper(confirmation) == "YES")
                    {
                        if(player[currentTurn - 1].getBalance() - buyBackCost >= 0)
                        {
                            int playerBal = player[currentTurn - 1].getBalance();
                            int difference = playerBal - buyBackCost;
                            player[currentTurn - 1].setBalance(difference);
                            property[unmorgageResponse].setMorgage(false);
                            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Congrats on unmorgaging your property!" << endl;
                        }
                        else
                        {
                            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Looks like you do not have enough cash in your pockets." << endl;
                        }
                    }
                    else if(toupper(confirmation) == "NO")
                    {

                    }
                    else
                    {
                        cout << "INVALID INPUT" << endl;
                    }
                }
            }
            else
            {
                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " You are not the owner of this property or this property is not morgaged!" << endl;
            }
        }
    }
    else
    {
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " You currently do not have any morgaged properties!" << endl;
    }
}