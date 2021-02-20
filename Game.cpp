#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
//01001110 01101001 01100011 01100101 00100001 00100001 00100000 01000101 01100001 01110011 01110100 01100101 01110010 00100000 01000101 01100111 01100111 00101100 00100000 01101000 01110101 01101000 00111111 00001101 00001010 00100000 00100000 00100000 01011111 00001101 00001010 00100000 00100111 00100000 00100000 00100000 00100111 00001101 00001010 00100111 00100000 00100000 00100000 00100000 00100000 00100111 00001101 00001010 00100000 00100111 00100000 01011111 00100000 00100111 00001101 00001010 00100000
using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string Game::toupper(string name) //A function to turn the string entered into all capital leters
{
    int length = name.length(); //Obtains the length of the string
    string newname;
    for(int i = 0; i < length; i++) //Cycles through all of the characters of the entered string.
    {
        if(name[i] >= 97 && name[i] <= 122) //Checks if characher is a lowercase letter using ascii values.
        {
            char newchar = name[i] - 32; //Obtains its capital leter equivalent.
            newname = newname + newchar;
        }
        else
        {
            newname = newname + name[i];
        }
    }
    return newname;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Game constructor
Game::Game()
{
    dice_1 = 0;
    dice_2 = 0;
    currentTurn = 1;
    numPlayers = 0;
    
    //Initialized Tabula Rasa Board
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                for(int l = 0; l < 2; l++)
                {
                    //Fills outer board with #
                    if(!((1 <= i && i <= 9) && (1 <= j && j <= 9)))
                    {
                        map[i][j][k][l] = '#';
                    }
                    else
                    {
                        // Empty space of the board
                        // A 9 by 9 empty space
                        map[i][j][k][l] = ' ';
                    }
                    //This if statement adds borders and spaces 
                    if(((l % 2) != 0) && !((1 <= i && i <= 9) && (1 <= j && j <= 9)) || (j == 9 && l == 1))
                    {
                        map[i][j][k][l] += " |";
                    }
                    else
                    {
                        map[i][j][k][l] += "  ";
                    }
                    map[i][j][k][l] += ' ';
                }
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::roll()
{
    srand((unsigned)time(0));
    for(int i = 0; i < 2; i++)
    {
        dice_1 = rand() % 6 + 1;
        dice_2 = rand() % 6 + 1;
    }

    /*
    This part will allow the player to roll again if they roll two dice of the same time.
    It will function by taking in both of the dice roll variables and comparing them to each other.
    If they are the same, it will move you and allow you to roll again after performing other tasks.
    */

    if(dice_1 == dice_2)
    {
        player[currentTurn - 1].setDisplayStatus(true);
    }
    if(dice_1 != dice_2)
    {
        player[currentTurn - 1].setDisplayStatus(false);
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::rent(int propertyLocation, int currentTurn)
{
    /*
    This function will allow it so that if the player lands on a property already owned, it will check if it is owned,
    determine how much rent is owed due to the rent array in the property array, and subtract the balance from the player
    while adding that amount to the owner.
    */

   int rentCost = property[propertyLocation].getRent();
   string ownerOfProperty = property[propertyLocation].getOwner();
   int unfortunate_player_bal = player[currentTurn - 1].getBalance();
   bool morgageStatus = property[propertyLocation].getMorgage_Status();
   if(!morgageStatus)
   {
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " --> " << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "]" << "\x1B[0m" << " Looks like you will need to pay some rent to " << "\x1B[91m" << property[propertyLocation].getOwner() << "\x1B[0m" << " @ [" << property[propertyLocation].getPropertyLocation() << "] " << property[propertyLocation].getPropertyName() << endl;
        if((unfortunate_player_bal - rentCost) < 0)
        {
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like you will need to sell some houses to pay off that rent." << endl;
            if(listOfOwnedProperties() != 0)
            {
                morgage();
            }
            else
            {
                bankrupt();
            }
        }
        if((unfortunate_player_bal - rentCost) >= 0)
        {
            for(int i = 0; i < numPlayers; i++)
            {
                if(player[i].getName() == ownerOfProperty)
                {
                    int fortunate_player_bal = player[i].getBalance();
                    // cout << "Current Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;
                    fortunate_player_bal += rentCost;
                    player[i].setBalance(fortunate_player_bal);
                    // cout << "New Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;

                    cout << "Transaction Process: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[91m" << " - $" << rentCost << "\x1B[0m" << endl;
                    unfortunate_player_bal -= rentCost;
                    player[currentTurn - 1].setBalance(unfortunate_player_bal);
                    cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[0m" << endl << endl;
                }
            }
        }
   }
   else
   {
       cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your in Luck! " << property[propertyLocation].getPropertyName() << " has been morgaged by " << property[propertyLocation].getOwner() << endl;
   }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::waterElectricRent()
{
    /*
    If the player lands on a utility that someone else owns, it determines if they own one or both utility,
    and performs a calculation based on whatever they rolled to land on that spot. The multiplier is changed based
    on if they own one or both properties. This money is subtracted from the player's balance and added to the
    owner's balance.
    */
   string ownerOfProperty = property[player[currentTurn - 1].getBoardLocation()].getOwner();
   int unfortunate_player_bal = player[currentTurn - 1].getBalance();
   for(int i = 0; i < numPlayers; i++)
    {
        if(toupper(player[i].getName()) == toupper(property[player[currentTurn - 1].getBoardLocation()].getOwner()))
        {
            if(toupper(property[28].getOwner()) == toupper(property[12].getOwner()))
            {
                    if((unfortunate_player_bal - (10 * (dice_1 + dice_2))) < 0)
                    {
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like you will need to sell some houses to pay off that rent." << endl;
                        // Morgage Function here
                        morgage();
                    }
                    else
                    {
                        int fortunate_player_bal = player[i].getBalance();
                        // cout << "Current Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;
                        fortunate_player_bal = fortunate_player_bal + 10 * (dice_1 + dice_2);
                        player[i].setBalance(fortunate_player_bal);
                        // cout << "New Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;

                        cout << "Transaction Process: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[91m" << " - $" << 10 * (dice_1 + dice_2) << "\x1B[0m" << endl;
                        unfortunate_player_bal = unfortunate_player_bal - (10 * (dice_1 + dice_2));
                        player[currentTurn - 1].setBalance(unfortunate_player_bal);
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[0m" << endl;
                    }
                }
                else
                {
                    if((unfortunate_player_bal - (4 * (dice_1 + dice_2))) < 0)
                    {
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like you will need to sell some houses to pay off that rent." << endl;
                        // Morgage Function here
                        morgage();
                    }
                    else
                    {
                        int fortunate_player_bal = player[i].getBalance();
                        // cout << "Current Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;
                        fortunate_player_bal += 4 * (dice_1 + dice_2);
                        player[i].setBalance(fortunate_player_bal);
                        // cout << "New Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;

                        cout << "Transaction Process: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[91m" << " - $" << 4 * (dice_1 + dice_2) << "\x1B[0m" << endl;
                        unfortunate_player_bal -= 4 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(unfortunate_player_bal);
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[0m" << endl;  
                    }
                }
            }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::luxuryTax()
{
    /*
     If the player lands on the luxury tax spot, they will have 75 dollars subtracted from their balance.
    */
    cout << property[player[currentTurn - 1].getBoardLocation()].getPropertyName() << endl;
    int amount = player[currentTurn - 1].getBalance();
    amount = amount - 75;
    player[currentTurn - 1].setBalance(amount);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::incomeTax()
{
    /*
    If the player lands on this spot, they are given the option of paying either 200 dollars or 10% of their balance. This
    function will allow them to choose and will perform the subtractions from their balance after the player chooses.
    */
    cout << property[player[currentTurn - 1].getBoardLocation()].getPropertyName() << endl;
    int repeater = 1;
    while(repeater == 1)
    {
        cout << "Press 1 to pay $200. Press 2 to pay 10% of your balance." << endl;
        int entry;
        cin >> entry;
        switch(entry)
        {
            case 1:
            {
                cout << "Player " << player[currentTurn - 1].getName() << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 200;
                player[currentTurn - 1].setBalance(amount);
                repeater = 0;
                break;
            }
            case 2:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - (amount * 0.1);
                player[currentTurn - 1].setBalance(amount);
                repeater = 0;
                break;
            }
            default:
            {
                cout << "Invalid input" << endl;
                incomeTax();
            }
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::passGo()
{
    /*
    When the player passes go, this function will automatically add 200 dollars to their balance.
    */
    int amount = player[currentTurn - 1].getBalance();
    amount = amount + 200;
    player[currentTurn - 1].setBalance(amount);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Game::checkForExceptions(int boardLocation_)
{
    switch(boardLocation_)
    {
        //Cannot be owned
        case 0: case 2: case 4: case 7: case 10: case 17:
        case 20: case 22: case 30: case 33: case 36: case 38:
        {
            int individual_boardLocation = boardLocation_;
            switch(individual_boardLocation)
            {
                case 0: //PassGo
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    passGo();
                    break;
                }
                case 2: case 17: case 33: //Community Chest
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    communityChest();
                    break;
                }
                case 4: //Income Tax
                {
                    incomeTax();
                    break;
                }
                case 7: case 22: case 36: //Chance
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    chance();
                    break;
                }
                case 10: //Just in Jail
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    break;
                }
                case 20: //Free Parking
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    break;
                }
                case 30: //Go to jail
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    break;
                }
                case 38: //Luxary Tax
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    luxuryTax();
                    break;
                }
            }
            return false;
            break;
        }
        //Can own properties
        case 1: case 3: case 6: case 8: case 9: case 11: case 13: case 14: case 16: case 18: case 19: case 21: 
        case 23: case 24: case 26: case 27: case 29: case 31: case 32: case 34: case 37: case 39: case 12: case 28:
        case 5: case 15: case 25: case 35:
        {
            return true;
            break;
        }
        default:
            cout << "MESSAGE FROM PROGRAM: [ERROR] BOARD LOCATION DOES NOT EXISTS" << endl;
    }     
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::checkOwnership(int currentTurn)
{
    int playerLocation = player[currentTurn - 1].getBoardLocation();
    string ownership_status = property[playerLocation].getOwner();

    if(checkForExceptions(playerLocation))
    {
        if(ownership_status == "none")
        {
            buy(playerLocation, currentTurn);
        }
        else if(ownership_status != player[currentTurn - 1].getName() && (player[currentTurn - 1].getBoardLocation() == 12 || player[currentTurn - 1].getBoardLocation() == 28))
        {
            waterElectricRent();
        }
        else if(ownership_status != player[currentTurn - 1].getName())
        {
            rent(playerLocation, currentTurn);
        }
        else if(ownership_status == player[currentTurn - 1].getName())
        {
            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Looks like you landed on one of your own properties! You're safe." << endl;
        }
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::morgage()
{
    int propertyLocation = player[currentTurn - 1].getBoardLocation();
    int rentCost = property[propertyLocation].getRent();
    
    int numPropertiesOwned = listOfOwnedProperties();


    if((numPropertiesOwned == 0) && ((player[currentTurn - 1].getBalance() - rentCost) < 0))
    {
        //Bankrupt Function can be placed here since morgage is used most of the time as a last resort
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Player " << property[propertyLocation].getOwner() << " has yeeted " << player[currentTurn - 1].getName() << "from the game!" << endl;
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Player " << "\x1B[91m" << player[currentTurn - 1].getName() << "\x1B[0m" << " You're bankrupt!" << endl;
        bankrupt();
    }
    else if(numPropertiesOwned != 0)
    {
        bool is_player_title_deeds = false;
        int uI_PropertyLoc;
        cout << "Enter Only Your Property Location that your want to morgage: ";
        cin >> uI_PropertyLoc;
        
        for(int i = 0; i < 40; i++)
        {
            if((0 <= uI_PropertyLoc && uI_PropertyLoc < 40) && (property[uI_PropertyLoc].getOwner() == player[currentTurn - 1].getName()) && (property[uI_PropertyLoc].getMorgage_Status() == false))
            {
                is_player_title_deeds = true;
            }
        }
        if(!is_player_title_deeds)
        {
            banish(currentTurn);
        }
        else
        {
            int propertyCost = property[uI_PropertyLoc].getPropertyCost();
            int morgagedCost = propertyCost / 2;
            int playerBalance = player[currentTurn - 1].getBalance();
            
            
            cout << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "]" << "\x1B[0m" << " Current Balance: " << "\x1B[92m" << "$" << playerBalance << "\x1B[97m" << " + $" << morgagedCost << "\x1B[0m" << endl;
            cout << "Expected Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() + morgagedCost << endl;
            string confirmation;
            cout << "Do you want to morgage this property: " << "\x1B[91m" << "[" << property[uI_PropertyLoc].getPropertyLocation() << "] " << property[uI_PropertyLoc].getPropertyName() << "\x1B[0m" << " for " << "$" << morgagedCost << "?" << endl; 
            cout << "Enter yes or no: ";
            cin >> confirmation;


            if(toupper(confirmation) == "YES")
            {
                if(property[uI_PropertyLoc].getNumBuildings() != 0)
                {
                    int sellNumHouses = 0;
                    int propertyNumBuildings = property[uI_PropertyLoc].getNumBuildings();
                    cout << endl;
                    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Looks like you will need to sell some of your houses/hotel in order to morgage your property!" << endl;
                    cout << "\x1B[91m" << "[Mr.Monopoly] [WARNING]" << "\x1B[0m" << " Each building will be sold for " << "\x1B[92m" << "$" << property[uI_PropertyLoc].getBuildingCost() / 2 << "\x1B[0m" << endl;
                    cout << endl;
                    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "You can sell " << propertyNumBuildings << " buildings. On property " << "[" << uI_PropertyLoc << "] " << property[uI_PropertyLoc].getPropertyName() << "." << endl;
                    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "How many buildings would you like to sell? ";
                    cin >> sellNumHouses;
                    if(cin.fail())
                    {
                        cout << "INVALID INPUT" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                    }
                    else
                    {
                        if(1 <= sellNumHouses && sellNumHouses <= 5 && sellNumHouses <= propertyNumBuildings)
                        {
                            int repeater = 0;
                            int soldHouseCost = (property[uI_PropertyLoc].getBuildingCost() / 2) * sellNumHouses;
                            int sum = playerBalance + soldHouseCost;
                            cout << endl;
                            cout << "Transaction Process: " << "\x1B[92m" << "$" << playerBalance << "\x1B[97m" << " + $" << soldHouseCost << "\x1B[0m" << endl;
                            cout << "Expected Balance: " << "\x1B[92m" << "$" << sum << "\x1B[0m" << endl;
                            do
                            {
                                string playerConfirmation;
                                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Would you like to sell " << sellNumHouses << " buildings for $" << soldHouseCost << endl;
                                cout << "Enter yes or no: ";
                                cin >> playerConfirmation;
                                if(toupper(playerConfirmation) == "YES")
                                {
                                    property[uI_PropertyLoc].setNumBuildings(propertyNumBuildings - sellNumHouses);
                                    player[currentTurn - 1].setBalance(sum);
                                    cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "You now have " << property[uI_PropertyLoc].getNumBuildings() << " buildings. The current rent is $" << property[uI_PropertyLoc].getRent() << endl;
                                    cout << "Current Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() << "\x1B[0m" << endl;
                                    repeater = 1;
                                }
                                else if (toupper(playerConfirmation) == "NO")
                                {
                                    repeater = 1;
                                }
                                else
                                {
                                    cout << "INVALID INPUT" << endl;
                                }
                            } while (repeater == 0);
                        }
                        else
                        {
                            cout << "You cannot sell more than " << propertyNumBuildings << "." << endl;
                        }
                    }
                }
                else
                {
                    property[uI_PropertyLoc].setMorgage(true);
                    player[currentTurn - 1].setBalance(playerBalance + morgagedCost);
                    cout << "You Morgaged property " << "\x1B[91m" << "[" << property[uI_PropertyLoc].getPropertyLocation() << "] " << property[uI_PropertyLoc].getPropertyName() << "\x1B[0m" << endl;
                }
                
            }
            else if(toupper(confirmation) == "NO")
            {
                //Returns back to player menu
            }
            else
            {
                cout << endl;
                cout << "\x1B[91m" << "Invalid Input. Type yes or no" << "\x1B[0m" << endl;
                morgage();
            }
        }
    }
}