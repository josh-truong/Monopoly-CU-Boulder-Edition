#include "Game.h"
#include <iostream>

using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::getPropertyInfo(int propertyLocation_)
{
    cout << "--------------------------------" << endl;
    cout << "\x1B[97m" << "[" << propertyLocation_ << "] " << property[propertyLocation_].getPropertyName() << "\x1B[0m" << endl;
    cout << "Owner: " << "\x1B[93m" << property[propertyLocation_].getOwner() << "\x1B[0m" << endl;
    
    if(propertyLocation_ != 2 && propertyLocation_ != 17 && propertyLocation_ != 33
        && propertyLocation_ != 7 && propertyLocation_ != 22 && propertyLocation_ != 36)
    {
        cout << "Property Price: \x1B[92m$" << property[propertyLocation_].getPropertyCost() << "\x1B[0m" << endl;
    }
    if(propertyLocation_ != 2 && propertyLocation_ != 17 && propertyLocation_ != 33
        && propertyLocation_ != 7 && propertyLocation_ != 22 && propertyLocation_ != 36 && propertyLocation_ != 12 && propertyLocation_ != 28)
    {
        cout << "Current Rent Cost: \x1B[92m$" << property[propertyLocation_].getRent() << "\x1B[0m" << endl;
    }
    
    switch(propertyLocation_)
    {
        // 2, 17, 33 C_Chest| 7, 22, 36 Chance| 0, 4, 10, 20, 33, 38 Non-Ownables
        case 0: case 2: case 4: case 7: case 10: case 17:
        case 20: case 22: case 30: case 33: case 36: case 38: 
        {
            // There's nothing extra to print
            break;
        }
        case 12: case 28: //Electric and water works
        {
            cout << "Property Price: \x1B[92m$" << property[propertyLocation_].getPropertyCost() << "\x1B[0m" << endl;                                                                                                                                
            //INDIVIDUAL CASES ARE NOT COMPLETED
            break;
        }
        case 5: case 15: case 25: case 35: //Transports
        {
            int numTransportsOwned = 0;
            for(int i = 0; i < getNumPlayers(); i++)
            {
                for(int j = 5; j < 39; j += 10)
                {
                    if(property[j].getOwner() == player[i].getName() && property[propertyLocation_].getOwner() != "none")
                    {
                        numTransportsOwned++;
                        // cout << property[j].getOwner() << " == " << player[i].getName() << " && " << property[j].getOwner() << " != none" << endl;
                    }
                }
            }
            cout << "Number of transport services owned: \x1B[97m" << numTransportsOwned << "\x1B[0m" << endl;
            property[propertyLocation_].getListOfRentTransport();
            break;
        }
        case 1: case 3: case 6: case 8: case 9: case 11: case 13: case 14: case 16: case 18: case 19: case 21: 
        case 23: case 24: case 26: case 27: case 29: case 31: case 32: case 34: case 37: case 39:
        {
            cout << "Property Color: " << property[propertyLocation_].getColor() << endl;
            cout << "Building cost: \x1B[92m$" << property[propertyLocation_].getBuildingCost() << "\x1B[0m" << endl;
            cout << "Number of buildings built: \x1B[97m" << property[propertyLocation_].getNumBuildings() << "\x1B[0m" << endl;
            property[propertyLocation_].getListOfRentCP();
            break;
        }
        default:
            cout << "Your request for property " << propertyLocation_ << " does not exist" << endl;
    }
    cout << endl;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::listOfOwnedProperties()
{
    int nonMorgaged_property_counter = 0;
    int allProperties = 0;
    cout << "----------Owned Properties----------" << endl;
    for(int i = 0; i < 40; i++)
    {
        string owned_PropertyName = property[i].getPropertyName();
        int propertyRent = property[i].getRent();
        int propertyCost = property[i].getPropertyCost();
        int morgagedCost = propertyCost / 2;
        int numBuildings = property[i].getNumBuildings();
        string color = toupper(property[i].getColor());
        if((property[i].getOwner() == player[currentTurn - 1].getName()) && (property[i].getMorgage_Status() == false))
        {
            cout << "\x1B[92m" << "[" << i << "] " << owned_PropertyName << "\x1B[0m" << " | Price: \x1B[92m$" << propertyCost << "\x1B[0m" << " | Morgaged Value: \x1B[91m$" << morgagedCost << "\x1B[0m" << " | Buildings Built: " << numBuildings <<  " | Current Rent: \x1B[91m$" << propertyRent << "\x1B[0m" << " | Color: " << color << endl;
            nonMorgaged_property_counter++;
            allProperties++;
        }
        else if((property[i].getOwner() == player[currentTurn - 1].getName()) && (property[i].getMorgage_Status() == true))
        {
            cout << "\x1B[91m" << "[Morgaged Property] [" << i << "] " << owned_PropertyName << "\x1B[0m" << " | Unmortgage Price: " << "\x1B[91m" << "$" << (propertyCost + (propertyCost * 0.1)) << "\x1B[0m" << " | Color: " << color << endl;
            allProperties++;
        }
        
    }
    if(allProperties == 0)
    {
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You currently do not own any properties" << endl;
    }
    cout << endl;
    return nonMorgaged_property_counter;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Game::listOfOwnedProperties_ByOtherPlayers()
{
    int spyPlayer;
    for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getName() != player[currentTurn - 1].getName() && player[i].getBankruptStatus() != true)
        {
            cout << "\x1B[92m" << "[" <<  i + 1 << "] " << "\x1B[0m" << player[i].getName() << "      ";
        }
    }
    cout << endl;
    do
    {
        cout << "Which Player do you want to Check? (Enter from a range of 1 to " << numPlayers << "): ";
        cin >> spyPlayer;
    }while(!(1 <= spyPlayer && spyPlayer <= numPlayers));
    spyPlayer -= 1;
    cout << endl;
    cout << "\x1B[92m" << "[" << player[spyPlayer].getName() << "]" << "\x1B[0m" << " Current Balance: " << "\x1B[92m" << "$" << player[spyPlayer].getBalance() << "\x1B[0m" << endl;
    int nonMorgaged_property_counter = 0;
    int allProperties = 0;
    cout << "----------Owned Properties----------" << endl;
    for(int i = 0; i < 40; i++)
    {
        string owned_PropertyName = property[i].getPropertyName();
        int propertyRent = property[i].getRent();
        int propertyCost = property[i].getPropertyCost();
        int morgagedCost = propertyCost / 2;
        string color = toupper(property[i].getColor());
        if((property[i].getOwner() == player[spyPlayer].getName()) && (property[i].getMorgage_Status() == false))
        {
            cout << "[" << i << "] " << owned_PropertyName << " | Price: \x1B[92m$" << propertyCost << "\x1B[0m" << " | Morgaged Value: \x1B[91m$" << morgagedCost << "\x1B[0m" << " | Current Rent: \x1B[91m$" << propertyRent << "\x1B[0m" << " | Color: " << color << endl;
            nonMorgaged_property_counter++;
            allProperties++;
        }
        else if((property[i].getOwner() == player[spyPlayer].getName()) && (property[i].getMorgage_Status() == true))
        {
            cout << "\x1B[91m" << "[Morgaged Property] [" << i << "] " << owned_PropertyName << "\x1B[0m" << " | Unmortgage Price: " << "\x1B[91m" << "$" << (propertyCost + (propertyCost * 0.1)) << "\x1B[0m" << " | Color: " << color << endl;
            allProperties++;
        }
        
    }
    if(allProperties == 0)
    {
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " There's Currently No Title Deeds Owned" << endl;
    }
    cout << endl;
    return nonMorgaged_property_counter;
}