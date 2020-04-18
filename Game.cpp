#include "Game.h"
#include "Property.h"
#include "Player.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <sstream>
//01001110 01101001 01100011 01100101 00100001 00100001 00100000 01000101 01100001 01110011 01110100 01100101 01110010 00100000 01000101 01100111 01100111 00101100 00100000 01101000 01110101 01101000 00111111 00001101 00001010 00100000 00100000 00100000 01011111 00001101 00001010 00100000 00100111 00100000 00100000 00100000 00100111 00001101 00001010 00100111 00100000 00100000 00100000 00100000 00100000 00100111 00001101 00001010 00100000 00100111 00100000 01011111 00100000 00100111 00001101 00001010 00100000
using namespace std; 


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

//Game constructor
Game::Game()
{
    dice_1 = 0;
    dice_2 = 0;
    currentTurn = 1;
    inJail = false;
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

/*
    set a piece on the board. Using the boardlocation to place a piece into the board
    playerPiece must only take in a single character. ex) $,%,*,@,#
*/
void Game::setPiece(int boardLocation, string playerPiece, int currentTurn)
{
    int i,j;
    int k = player[currentTurn - 1].getPlayerPos_x();
    int l = player[currentTurn - 1].getPlayerPos_y();
    //Converts boardLocation into x and y coordinates

    /*
          2
        1|_|3
          0
    */
    if((boardLocation / 10) == 0) 
    {
        //Bottom Board - side 0
        i = 10;
        j = 10 - (boardLocation % 10);
    }
    else if((boardLocation / 10) == 1)
    {
        //Left Board - side 1
        i = 10 - boardLocation % 10;
        j = 0;
    }
    else if((boardLocation / 10) == 2)
    {
        //Top Board - side 2
        i = 0;
        j = boardLocation % 10;
    }
    else if((boardLocation / 10) == 3)
    {
        //Right Board - side 3
        i = boardLocation % 10;
        j = 10;
    }
    //////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////
    //Set piece into location
    if(!((1 <= i && i <= 9) && (1 <= j && j <= 9)))
    {
        map[i][j][k][l] = playerPiece;
    }
    else
    {
        map[i][j][k][l] = ' ';
    }
    if(((l % 2) != 0) && !((1 <= i && i <= 9) && (1 <= j && j <= 9)) || (j == 9 && l == 1))
    {
        map[i][j][k][l] += " |";
    }
    else
    {
        map[i][j][k][l] += "  ";
    }
    map[i][j][k][l] += " ";
}

void Game::erase(int currentTurn)
{
    string octothrop;
    //Replace and reset Player Previous Location with an octothrop
    octothrop = "#";
    int oldBoardLocation = player[currentTurn - 1].getPreviousBoardLocation();
    setPiece(oldBoardLocation, octothrop, currentTurn);
}

//Move is used to move a player when they roll the dice
void Game::move(int currentTurn)
{
    int boardLocation;
    string playerPiece;
    bool resetPosition = player[currentTurn - 1].getResetLocation_Status();

    for(int i = 1; i <= 2; i++)
    {
        if(resetPosition && (i == 2))
        {
            erase(currentTurn);
        }
        if(i == 1)
        {
            string playerPieces[4] = {"\x1B[92m$\x1B[0m",    "\x1B[92m%\x1B[0m",     "\x1B[92m*\x1B[0m",     "\x1B[92m&\x1B[0m"};
            player[currentTurn - 1].setBoardLocation(player[currentTurn - 1].getBoardLocation() + dice_1 + dice_2);
            playerPiece = playerPieces[currentTurn - 1];
            int newBoardLocation = player[currentTurn - 1].getBoardLocation();
            setPiece(newBoardLocation, playerPiece, currentTurn);
        }

    }
    //This is used only once at the beginning of the game
    player[currentTurn - 1].setResetLocation_TRUE();
}

void Game::display_MapAndPlayer() const
{
    //4d array - This allows for fixed position of character while knowing which player is on which square
        /*arr[i][j][k][l] <-- I and J represent the number of squares in a monopoly board (11 by 11)
            //k and l are the position of each player. This will not be change under any circumstance to change the player position use i and j
        */
    //This is where the map will be displayed
    string firstRowConcatOfK, secondRowConcatOfK;
    int topLinecounter = 20;
    int leftLineCounter = 20;
    int rightLineCounter = 30;
    for(int oneLine = 0; oneLine < 11; oneLine++)
    {
        cout << "      " << topLinecounter; 
        topLinecounter++;
    }
    cout << endl;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                for(int l = 0; l < 2; l++)
                {
                    // cout << "i: " << i << " j: " << j  << " k: " << k << " l: " << l << endl;
                    if(k == 0) //OMG I forgot the other = and it kept on going to inf
                    {
                        firstRowConcatOfK += map[i][j][k][l];
                        //cout << firstRowConcatOfK << endl;
                    }
                    else
                    {
                        secondRowConcatOfK += map[i][j][k][l];
                    }
                    
                }
                
            }
        }
        if(rightLineCounter == 40)
        {
            rightLineCounter = 0;
        }
        cout << leftLineCounter << " | " << firstRowConcatOfK << endl << "   | " << secondRowConcatOfK << rightLineCounter << endl;
        leftLineCounter--;
        rightLineCounter++;
        if(0 <= i && i < 10)
        {
            cout << "   ---------" << setw(80) << "---------" << endl;
        }
        firstRowConcatOfK = "";
        secondRowConcatOfK = "";
    }
    
    int bottomLinecounter = 10;
    for(int oneLine = 0; oneLine < 11; oneLine++)
    {
        cout << "      " << bottomLinecounter << " "; 
        bottomLinecounter--;
    }
    cout << endl;
}



bool Game::readPlayers()
{
    //Read Player files
    cout << "How many players? (2-4): " << endl;
    cin >> numPlayers;
    ifstream readPlayerFile;
    string line, x_pos, y_pos, playerChar_, playerName;
    readPlayerFile.open("player.csv");
    if(readPlayerFile.fail())
    {
        cout << "Error. Could not read player file." << endl;
        return false;
    }
    else
    {
        if(!(2 <= numPlayers && numPlayers <= 4))
        {
            cout << "Invalid Range of players" << endl << endl;
            return false;
        }
        else
        {
            for(int i = 0; i <= numPlayers; i++)
            {
                getline(readPlayerFile, line);
                istringstream strm;
                strm.str(line);
                getline(strm, x_pos, ',');
                getline(strm, y_pos, ',');
                getline(strm, playerChar_, ',');
                if(i != 0)
                {
                    cout << "\n(" << i << ") Enter a player name: ";
                    cin >> playerName;
                    
                    for(int j = 0; j < getNumPlayers(); j++)
                    {
                        while(player[j].getName() == playerName)
                        {
                            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "That Username Has Already Been Taken!" << endl;
                            cout << "\n(" << i << ") Enter a player name: ";
                            cin >> playerName;
                        }
                    }

                    player[i - 1].setName(playerName);
                    player[i - 1].setPlayerChar(playerChar_);
                    cout << "Player Character: " << player[i - 1].getPlayerChar() << endl;
                    player[i - 1].setPlayerPos(stoi(x_pos), stoi(y_pos));
                }
            }
            // for(int i = 0; i < numPlayers; i++)
            // {
            //     cout << setw(20) << player[i].getName() << " (" << player[i].getPlayerChar() << ')' << endl;
            //     cout << setw(20) << "Balance: " << player[i].getBalance() << endl;
            //     cout << setw(20) << '(' << player[i].getPlayerPos_x() << ", " << player[i].getPlayerPos_y() << ')' << endl;
            // }
            readPlayerFile.close();
            return true;
        }
        
    }
}
//Return the number of players
int Game::getNumPlayers()
{
    return numPlayers;
}

//Will intialize the property of the board after reading the file
void Game::readProperty()
{
    string line, propertyLocation_str;
    ifstream readPropertyFile;
    readPropertyFile.open("property.csv");
    if(readPropertyFile.fail())
    {
        cout << "Boi you failed somewhere cause you got an error for readProperty file." << endl;
        cout << "The file probably doesn't exist." << endl;
        exit(-1);
    }
    for(int i = 0; i <= (40 + 1); i++) //<-- The number 23 represents how many buildings, the extra +1 comes from the 2nd header()
    {
        getline(readPropertyFile, line);
        if(i != 0 && i!= 1) //Will skip the first line
        {
            istringstream strm;
            strm.str(line);
            getline(strm, propertyLocation_str, ',');

            int propertyLocation_int = stoi(propertyLocation_str);
            
            switch(propertyLocation_int)
            {
                //All these cases 
                // Note that cases 12, 28
                    // ^ Those are electric company, water works,
                    //Those are cases which we can do, i have no idea how to implement the other cases
                    //when the players land on those. At least for now
                
                // 2, 17, 33 C_Chest| 7, 22, 36 Chance| 0, 4, 10, 20, 33, 38 Non-Ownables
                case 0: case 2: case 4: case 7: case 10: case 17:
                case 20: case 22: case 30: case 33: case 36: case 38: 
                {
                    string NON_OP;
                    getline(strm, NON_OP, ',');
                    property[propertyLocation_int].setOwner("\x1B[93m Mr.Monopoly (Rich Uncle Pennybags) \x1B[0m \x1B[31m \n-----THIS PROPERTY CANNOT BE OWNED!----- \x1B[0m");
                    property[propertyLocation_int].setPropertyName(NON_OP);
                    property[propertyLocation_int].setPropertyLocation(propertyLocation_int);
                    break;
                }
                case 12: case 28: // electric company and water works
                {
                    string company;
                    getline(strm, company, ',');
                    property[propertyLocation_int].setPropertyName(company);
                    property[propertyLocation_int].setPropertyLocation(propertyLocation_int);
                    // cout << "IDK Cases: " << propertyLocation_int << endl;
                    //INDIVIDUAL CASES ARE NOT COMPLETED
                    break;
                }
                //case 5, 15, 25, 35 are railroads
                case 5: case 15: case 25: case 35:
                {
                    string transportName_, transportCost_, transportRent_;
                    getline(strm, transportName_, ',');
                    getline(strm, transportCost_, ',');
                    for(int i = 0; i < 4; i++)
                    {
                        getline(strm, transportRent_, ',');
                        property[propertyLocation_int].setRentAt(i, stoi(transportRent_));
                    }

                    property[propertyLocation_int].setPropertyLocation(propertyLocation_int);
                    property[propertyLocation_int].setPropertyName(transportName_);
                    property[propertyLocation_int].setPropertyCost(stoi(transportCost_));
                    break;
                }
                case 1: case 3: case 6: case 8: case 9: case 11: case 13: case 14: case 16: case 18: case 19: case 21: 
                case 23: case 24: case 26: case 27: case 29: case 31: case 32: case 34: case 37: case 39:
                {
                    // cout << "Colored Property: " << propertyLocation_int << endl;
                    string propertyName_, property_cost_, building_cost_;
                    // string rent_,house1_,house2_,house3_,house4_,hotel_, color_;
                    string rent_, color_;
                    
                    getline(strm, propertyName_, ',');
                    getline(strm, property_cost_, ',');
                    getline(strm, building_cost_, ',');
                    for(int i = 0; i < 6; i++)
                    {
                        getline(strm, rent_, ',');
                        property[propertyLocation_int].setRentAt(i, stoi(rent_));
                    }
                    getline(strm, color_, ',');
                    
                    property[propertyLocation_int].setPropertyLocation(propertyLocation_int);
                    property[propertyLocation_int].setPropertyName(propertyName_);
                    property[propertyLocation_int].setPropertyCost(stoi(property_cost_));
                    property[propertyLocation_int].setBuildingCost(stoi(building_cost_));
                    property[propertyLocation_int].setColor(color_);
                    break;
                }
                default:
                    cout << "ERROR. For loop is out of sync" << endl;
                    break;
                    
            }
        }
    }
    readPropertyFile.close();
}

void Game::getPropertyInfo(int propertyLocation_)
{
    cout << "--------------------------------" << endl;
    cout << "\x1B[97m" << "[" << propertyLocation_ << "] " << property[propertyLocation_].getPropertyName() << "\x1B[0m" << endl;
    cout << "Owner: " << "\x1B[93m" << property[propertyLocation_].getOwner() << "\x1B[0m" << endl;
    
    if(propertyLocation_ != 2 && propertyLocation_ != 17 && propertyLocation_ != 33
        && propertyLocation_ != 7 && propertyLocation_ != 22 && propertyLocation_ != 36)
    {
        cout << "Property Price: \x1B[92m$" << property[propertyLocation_].getPropertyCost() << "\x1B[0m" << endl;
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
            //INDIVIDUAL CASES ARE NOT COMPLETED
            break;
        }
        case 5: case 15: case 25: case 35: //Transports
        {
            cout << "Number of transport services owned: \x1B[97m" << property[propertyLocation_].getNumBuildings() << "\x1B[0m" << endl;
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
            cout << "Error @ getPropertyInfo()" << endl;
            cout << "Possible Error" << endl;
            cout << "Your request for property " << propertyLocation_ << " does not exist" << endl;
            cout << "The property you requested does not have a case and is still in the works" << endl;
    }
    cout << endl;
}


void Game::roll()
{
    srand((unsigned)time(0));
    for(int i = 0; i < 2; i++)
    {
        dice_1 = rand() % 6 + 1;
        dice_2 = rand() % 6 + 1;
    }
    // cout << "dice_1: " << dice_1 << endl;
    // cout << "dice_2: " << dice_2 << endl;
}



void Game::endTurn()
{
    /*
    The end game function will allow a player to end their turn by typing in "end".
    They current turn will move to the next player and display which player's turn it is.
    */

    currentTurn = (currentTurn % numPlayers) + 1;
    cout << "It is player " << currentTurn << "'s turn." << endl;

}

void Game::doubleTurn(int dice_1, int dice_2)
{
    /*
    This function will allow the player to roll again if they roll two dice of the same time.
    It will function by taking in both of the dice roll variables and comparing them to each other.
    If they are the same, it will move you and allow you to roll again after performing other tasks.
    */
}

void Game::endGame(string quit_)
{
    /*
    This function will allow the users to end the game whenver they feel like it by typing in quit. This will allow for 
    the users to quit if they wish to but could also allow you to calculate the response if someone wins by setting up
    a condition to activate it in main. It print a message to a text file that will display the results and the winner, 
    along with their balances.
    */
}


void Game::trade(string playerName, string propertyoffer, int offer_, string propertywanted)
{
    /*
    This function allows the user to offer a trade to another player. It takes the name of the player, the property you want to offer,
    and the amount of money you want to offer. It will then allow the person being offered to decide if they want to accept the offer or not.
    If they accepted the offer, it will transfer the money and exchange the properties.
    */
}

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
        //WARNING -- We do not have morgage function yet
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
            if(propertyLocation == 5 || propertyLocation == 15 || propertyLocation == 25 || propertyLocation == 35)
            {
                if(propertyLocation != 5 && property[propertyLocation].getOwner() == property[5].getOwner())
                {
                    property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
                    property[5].setNumBuildings(property[5].getNumBuildings() + 1);
                }
                if(propertyLocation != 15 && property[propertyLocation].getOwner() == property[15].getOwner())
                {
                    property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
                    property[15].setNumBuildings(property[15].getNumBuildings() + 1);
                }
                if(propertyLocation != 25 && property[propertyLocation].getOwner() == property[25].getOwner())
                {
                    property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
                    property[25].setNumBuildings(property[25].getNumBuildings() + 1);
                }
                if(propertyLocation != 35 && property[propertyLocation].getOwner() == property[35].getOwner())
                {
                    property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
                    property[35].setNumBuildings(property[35].getNumBuildings() + 1);
                }
            }
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Congratulations, " << property[propertyLocation].getOwner() << "! You're the proud owner of " << property[propertyLocation].getPropertyName() << "." << endl;
        }
        else if(toupper(playerResponse) == "N")
        {
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " I'm sorry to hear that." << endl;
            //WARNING -- We need to create and call an auction property
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
        //WARNING -- We need to create and call an auction property
    }
}

void Game::buyHouse(int propertyLocation, int currentTurn)
{
    /*
    This function will allow the user to buy a house for one of their properties. It will obtain the house cost from the property
    array and move the rent array down one position. It will also subtract the house cost from the player's balance.
    */
    string owner = property[propertyLocation].getOwner();
    if(toupper(owner) == toupper(player[currentTurn - 1].getName())
    {
        if(property[propertyLocation].getOwner() == property[1].getOwner() && property[propertyLocation].getOwner() == property[3].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five on one property." << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(property[propertyLocation].getOwner() == property[6].getOwner() && property[propertyLocation].getOwner() == property[8].getOwner() && property[propertyLocation].getOwner() == property[9].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five" << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(property[propertyLocation].getOwner() == property[11].getOwner() && property[propertyLocation].getOwner() == property[13].getOwner() && property[propertyLocation].getOwner() == property[14].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five" << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(property[propertyLocation].getOwner() == property[16].getOwner() && property[propertyLocation].getOwner() == property[18].getOwner() && property[propertyLocation].getOwner() == property[19].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five" << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(property[propertyLocation].getOwner() == property[21].getOwner() && property[propertyLocation].getOwner() == property[23].getOwner() && property[propertyLocation].getOwner() == property[24].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five" << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(property[propertyLocation].getOwner() == property[26].getOwner() && property[propertyLocation].getOwner() == property[28].getOwner() && property[propertyLocation].getOwner() == property[29].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five" << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(property[propertyLocation].getOwner() == property[31].getOwner() && property[propertyLocation].getOwner() == property[32].getOwner() && property[propertyLocation].getOwner() == property[34].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five" << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(property[propertyLocation].getOwner() == property[39].getOwner() && property[propertyLocation].getOwner() == property[39].getOwner())
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() <<"?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(userinput = "Y")
            {
                int repeater = 0;
                while(repeater == 1)
                {
                    cout << "How many houses would you like to buy? Maximum is five" << endl;
                    int input;
                    cin >> input;
                    switch(input)
                    {
                        case 1:
                        {
                            if(property[propertyLocation].getNumBuildings < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 2:
                        {
                            if(property[propertyLocation].getNumBuildings < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 3:
                        {
                            if(property[propertyLocation].getNumBuildings < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 4:
                        {
                            if(property[propertyLocation].getNumBuildings < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        case 5:
                        {
                            if(property[propertyLocation].getNumBuildings < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost(); << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                setNumBuildings(property[propertyLocation].getNumBuildings + 1);
                            }
                            else
                            {
                                cout << "Too many houses on this property." << endl;
                                repeater = 0;
                            }
                            break;
                        }
                        default:
                        {
                            cout "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(userinput = "N")
            {
                cin << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else
        {
            cout << "You do not own all corresponding properties." << endl;
        }
    }
    else
    {
        cout << "You must own the property to buy a house for the property." << endl; 
    }
}

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
                //Call the bankrupt function
                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like your time has run out!" << endl;
                cout << setw(50) << "\x1B[92m" << "Blucifer has entered the game and took you as his creator (Luis Jiménez)..." << endl;
                cout << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "] " << " has left the game." << endl;
            }
            
            
            // Morgage Function here
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

void Game::waterElectricRent(int rollone, int rolltwo, int propertyLocation)
{
    /*
    If the player lands on a utility that someone else owns, it determines if they own one or both utility,
    and performs a calculation based on whatever they rolled to land on that spot. The multiplier is changed based
    on if they own one or both properties. This money is subtracted from the player's balance and added to the
    owner's balance.
    */
   string ownerOfProperty = property[propertyLocation].getOwner();
   int unfortunate_player_bal = player[currentTurn - 1].getBalance();
   for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getName() == property[propertyLocation].getOwner())
        {
            if(property[28].getOwner() == property[12].getOwner())
            {
                    if((unfortunate_player_bal - (10 * (rollone + rolltwo))) < 0)
                    {
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like you will need to sell some houses to pay off that rent." << endl;
                        // Morgage Function here
                    }
                    else
                    {
                        int fortunate_player_bal = player[i].getBalance();
                        // cout << "Current Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;
                        fortunate_player_bal += 10 * (rollone + rolltwo);
                        player[i].setBalance(fortunate_player_bal);
                        // cout << "New Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;

                        cout << "Transaction Process: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[91m" << " - $" << 10 * (rollone + rolltwo) << "\x1B[0m" << endl;
                        unfortunate_player_bal -= 10 * (rollone + rolltwo);
                        player[currentTurn - 1].setBalance(unfortunate_player_bal);
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[0m" << endl;
                    }
                }
                else
                {
                    if((unfortunate_player_bal - (4 * (rollone + rolltwo))) < 0)
                    {
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like you will need to sell some houses to pay off that rent." << endl;
                        // Morgage Function here
                    }
                    else
                    {
                        int fortunate_player_bal = player[i].getBalance();
                        // cout << "Current Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;
                        fortunate_player_bal += 4 * (rollone + rolltwo);
                        player[i].setBalance(fortunate_player_bal);
                        // cout << "New Balance for " << player[i].getName() << " $" << fortunate_player_bal << endl;

                        cout << "Transaction Process: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[91m" << " - $" << 4 * (rollone + rolltwo) << "\x1B[0m" << endl;
                        unfortunate_player_bal -= 4 * (rollone + rolltwo);
                        player[currentTurn - 1].setBalance(unfortunate_player_bal);
                        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << unfortunate_player_bal << "\x1B[0m" << endl;  
                    }
                }
            }
        }
}

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
                amount = amount - amount * 0.1;
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

void Game::jail()
{
    /*
    This function will move a player directly to jail. It will then set a boolian to true which will remain true until three turns
    pass or the player succeeds in rolling a double. 
    */
    setPiece(10,player[currentTurn - 1].getPlayerChar(), currentTurn);
    erase(currentTurn);
    bool jail = true;
    player[currentTurn - 1].setJailStatus(jail);
}

void Game::passGo()
{
    /*
    When the player passes go, this function will automatically add 200 dollars to their balance.
    */
    int amount = player[currentTurn - 1].getBalance();
    amount = amount + 200;
    player[currentTurn - 1].setBalance(amount);
}

void Game::communityChest(string textfile)
{
    srand((unsigned)time(0));
    int result = rand() % 17 + 1;
    string line;
    ifstream communitychest;
    communitychest.open(textfile);
    if(communitychest.is_open())
    {
        int counter = 1;
        while(getline(communitychest, line) && counter < result)
        {
            counter++;
        }
        switch(result)
        {
            case 1:
            {
                cout << line << endl;
                setPiece(0,player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                passGo();
                break;
            }
            case 2:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 200;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 3:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 4:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 5:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 6:
            {
                cout << line  << endl;
                jail();
                break;
            }
            case 7:
            {
                cout << line  << endl;
                cout << line  << endl;
                for(int i = 0; i < numPlayers - 1; i++)
                {
                    int amount = player[currentTurn - 1].getBalance();
                    amount = amount + 50;
                    player[currentTurn - 1].setBalance(amount);
                }
                for(int j = 0; j < numPlayers; j++)
                {
                    if(currentTurn - 1 != j)
                    {
                        int amount = player[j].getBalance();
                        amount = amount - 50;
                        player[j].setBalance(amount);
                    }
                }
                break;
            }
            case 8:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 9:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 20;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 10:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 10;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 11:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 12:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 13:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 150;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 14:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 25;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 15:
            {
                cout << line  << endl;
                break;
            }
            case 16:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 10;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 17:
            {
                cout << line << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
        }
    }
    else
    {
        cout << "Text file failed to open." << endl;
    }
    /*
    This function will read the community chest textfile, generate a random number between 1 and 17, determine what message to print
    using a getline and while loop, and apply a specific effect based on the number they obtained (these effects will be in a switch)
    */  
}

void Game::chance(string textfile)
{
    srand((unsigned)time(0));
    int result = rand() % 16 + 1;
    string line;
    ifstream chance;
    chance.open(textfile);
    if(chance.is_open())
    {
        int counter = 1;
        while(getline(chance, line) && counter < result)
        {
            counter++;
        }
        switch(result)
        {
            case 1:
            {
                cout << line << endl;
                setPiece(0,player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                passGo();
                break;
            }
            case 2:
            {
                cout << line  << endl;
                if(player[currentTurn - 1].getBoardLocation() > 24)
                {
                    setPiece(24, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    passGo();
                }
                else
                {
                    setPiece(24, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                }
                break;
            }
            case 3:
            {
                cout << line  << endl;
                if(player[currentTurn - 1].getBoardLocation() > 11)
                {
                    setPiece(11, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    passGo();
                }
                else
                {
                    setPiece(11, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                }
                break;
            }
            case 4:
            {
                cout << line  << endl;
                int playerposition = player[currentTurn - 1].getBoardLocation();
                if(playerposition == 7)
                {
                    setPiece(12, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    string owner = property[12].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            cout << "Would you like to buy this property? Y for yes, N for no." << endl;
                            string answer;
                            cin >> answer;
                            if(answer == "Y")
                            {
                                buy(12, currentTurn);
                                repeater = 0;
                            }
                            else if(answer == "N")
                            {
                                repeater = 0;
                            }
                            else
                            {
                                cout << "Invalid input." << endl;
                            }
                        }
                    }
                    else
                    {
                        int amount = player[currentTurn - 1].getBalance();
                        amount = amount - 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amount);
                    }
                }
                else if(playerposition == 22)
                {
                    setPiece(28, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    string owner = property[28].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            cout << "Would you like to buy this property? Y for yes, N for no." << endl;
                            string answer;
                            cin >> answer;
                            if(answer == "Y")
                            {
                                buy(28, currentTurn);
                                repeater = 0;
                            }
                            else if(answer == "N")
                            {
                                repeater = 0;
                            }
                            else
                            {
                                cout << "Invalid input." << endl;
                            }
                        }
                    }
                    else
                    {
                        int amount = player[currentTurn - 1].getBalance();
                        amount = amount - 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amount);
                    }
                }
                else if(playerposition == 38)
                {
                    setPiece(12, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    string owner = property[12].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            cout << "Would you like to buy the property? Y for yes, N for no." << endl;
                            string answer;
                            cin >> answer;
                            if(answer == "Y")
                            {
                                buy(12, currentTurn);
                                repeater = 0;
                            }
                            else if(answer == "N")
                            {
                                repeater = 0;
                            }
                            else
                            {
                                cout << "Invalid input." << endl;
                            }
                        }
                    }
                    else
                    {
                        int amount = player[currentTurn - 1].getBalance();
                        amount = amount - 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amount);
                    }
                }
                break;
            }
            case 5:
            {
                cout << line  << endl;
                 int playerposition = player[currentTurn - 1].getBoardLocation();
                if(playerposition == 7)
                {
                    setPiece(15, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    string owner = property[15].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            cout << "Would you like to buy the property? Y for yes, N for no." << endl;
                            string answer;
                            cin >> answer;
                            if(answer == "Y")
                            {
                                buy(15, currentTurn);
                                repeater = 0;
                            }
                            else if(answer == "N")
                            {
                                repeater = 0;
                            }
                            else
                            {
                                cout << "Invalid input." << endl;
                            }
                        }
                    }
                    else
                    {
                        rent(15, currentTurn);
                    }
                }
                else if(playerposition == 22)
                {
                    setPiece(25, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    string owner = property[25].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            cout << "Would you like to buy the property? Y for yes, N for no." << endl;
                            string answer;
                            cin >> answer;
                            if(answer == "Y")
                            {
                                buy(25, currentTurn);
                                repeater = 0;
                            }
                            else if(answer == "N")
                            {
                                repeater = 0;
                            }
                            else
                            {
                                cout << "Invalid input." << endl;
                            }
                        }
                    }
                    else
                    {
                        rent(25, currentTurn);
                    }
                }
                else if(playerposition == 38)
                {
                    setPiece(5, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    string owner = property[5].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            cout << "Would you like to buy the property? Y for yes, N for no." << endl;
                            string answer;
                            cin >> answer;
                            if(answer == "Y")
                            {
                                buy(5, currentTurn);
                                repeater = 0;
                            }
                            else if(answer == "N")
                            {
                                repeater = 0;
                            }
                            else
                            {
                                cout << "Invalid input." << endl;
                            }
                        }
                    }
                    else
                    {
                        rent(5, currentTurn);
                    }
                }
                break;
            }
            case 6:
            {
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 50;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 7:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 8:
            {
                cout << line  << endl;
                setPiece(player[currentTurn - 1].getBoardLocation() - 3, player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);                
                break;
            }
            case 9:
            {
                cout << line  << endl;
                jail();
                break;
            }
            case 10:
            {
                cout << line  << endl;

                break;
            }
            case 11:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 15;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 12:
            {
                cout << line  << endl;
                if(player[currentTurn - 1].getBoardLocation() > 5)
                {
                    setPiece(5, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                    passGo();
                }
                else
                {
                    setPiece(5, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);
                }
                break;
            }
            case 13:
            {
                cout << line  << endl;
                setPiece(39, player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                break;
            }
            case 14:
            {
                cout << line  << endl;
                for(int i = 0; i < numPlayers - 1; i++)
                {
                    int amount = player[currentTurn - 1].getBalance();
                    amount = amount + 50;
                    player[currentTurn - 1].setBalance(amount);
                }
                for(int j = 0; j < numPlayers; j++)
                {
                    if(currentTurn - 1 != j)
                    {
                        int amount = player[j].getBalance();
                        amount = amount - 50;
                        player[j].setBalance(amount);
                    }
                }
                break;
            }
            case 15:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 150;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
            case 16:
            {
                cout << line  << endl;
                int amount = player[currentTurn - 1].getBalance();
                amount = amount + 100;
                player[currentTurn - 1].setBalance(amount);
                break;
            }
        }
    }
    else
    {
        cout << "Text file failed to open." << endl;
    }
    /*
    This function will read the chance textfile, generate a random number between 1 and 16, determine what message to print
    using a getline and while loop, and apply a specific effect based on the number they obtained (these effects will be in a switch)
    */  
}

string Game::getPlayerUsername_GAME(int i)
{
    return player[i - 1].getName();
}

string Game::getPlayerCharacter(int i)
{
    string playerPieces[4] = {"$","%","*","&"};
    return playerPieces[i - 1];
}


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
                    communityChest("communitychest.txt");
                    break;
                }
                case 4: //Income Tax
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    incomeTax();
                    break;
                }
                case 7: case 22: case 36: //Chance
                {
                    cout << property[boardLocation_].getPropertyName() << endl;
                    chance("chance.txt");
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

int Game::listOfOwnedProperties()
{
    int nonMorgaged_property_counter = 0;
    int allProperties = 0;
    for(int i = 0; i < 40; i++)
    {
        string owned_PropertyName = property[i].getPropertyName();
        int propertyRent = property[i].getRent();
        int propertyCost = property[i].getPropertyCost();
        int morgagedCost = propertyCost / 2;
        if((property[i].getOwner() == player[currentTurn - 1].getName()) && (property[i].getMorgage_Status() == false))
        {
            cout << "[" << i << "] " << owned_PropertyName << " | Price: \x1B[92m$" << propertyCost << "\x1B[0m" << " | Morgaged Value: \x1B[91m$" << morgagedCost << "\x1B[0m" << " | Current Rent: \x1B[91m$" << propertyRent << "\x1B[0m" << endl;
            nonMorgaged_property_counter++;
        }
        else if((property[i].getOwner() == player[currentTurn - 1].getName()) && (property[i].getMorgage_Status() == true))
        {
            cout << "\x1B[91m" << "[Morgaged Property] [" << i << "] " << owned_PropertyName << "\x1B[0m" << " | Unmortgage Price: " << "\x1B[91m" << "$" << (propertyCost + (propertyCost * 0.1)) << "\x1B[0m" << endl;
        }
        allProperties++;
    }
    if(allProperties == 0)
    {
        cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You currently do not own any properties" << endl;
    }
    cout << endl;
    //Add a menu for players to see property info
    return nonMorgaged_property_counter;
}

void Game::morgage()
{
    int propertyLocation = player[currentTurn - 1].getBoardLocation();
    int rentCost = property[propertyLocation].getRent();
    //Bankrupt Function can be placed here since morgage is used most of the time as a last resort
    int numPropertiesOwned = listOfOwnedProperties();


    if((numPropertiesOwned == 0) && ((player[currentTurn - 1].getBalance() - rentCost) < 0))
    {
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Player " << property[propertyLocation].getOwner() << " has yeeted " << player[currentTurn - 1].getName() << "from the game!" << endl;
        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Player " << "\x1B[91m" << player[currentTurn - 1].getName() << "\x1B[0m" << " You're bankrupt!" << endl;
        //Call the bankrupted function. Note that transitioning from array to vector might be neccessary
    }
    else
    {
        bool is_player_title_deeds = false;
        int uI_PropertyLoc;
        cout << "Enter Only Your Property Location that your want to morgage: ";
        cin >> uI_PropertyLoc;

        for(int i = 0; i < 40; i++)
        {
            if((property[uI_PropertyLoc].getOwner() == player[currentTurn - 1].getName()) && (property[uI_PropertyLoc].getMorgage_Status() == false))
            {
                is_player_title_deeds = true;
            }
        }


        if(!is_player_title_deeds)
        {
            banish(currentTurn);
            // I'm going to make a banishment feature
        }
        else
        {
            int propertyCost = property[uI_PropertyLoc].getPropertyCost();
            int morgagedCost = propertyCost / 2;
            int playerBalance = player[currentTurn - 1].getBalance();
            
            
            cout << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "]" << "\x1B[0m" << " Current Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() << "\x1B[97m" << " - $" << morgagedCost << "\x1B[0m" << endl;
            cout << "Expected Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() << endl;
            string confirmation;
            cout << "Do you want to morgage this property: " << "\x1B[91m" << "[" << property[uI_PropertyLoc].getPropertyLocation() << "] " << property[uI_PropertyLoc].getPropertyName() << "\x1B[0m" << " for " << "$" << morgagedCost << "?" << endl; 
            cout << "Enter yes or no: ";
            cin >> confirmation;


            if(toupper(confirmation) == "YES")
            {
                property[uI_PropertyLoc].setMorgage_True();
                player[currentTurn - 1].setBalance(playerBalance + morgagedCost);
                cout << "You Morgaged property " << "\x1B[91m" << "[" << property[uI_PropertyLoc].getPropertyLocation() << "] " << property[uI_PropertyLoc].getPropertyName() << "\x1B[0m" << endl;
            }
            else if(toupper(confirmation) == "NO")
            {
                checkOwnership(currentTurn);
            }
            else
            {
                cout << endl;
                cout << "\x1B[91m" << "Invalid Input. Type yes or no" << "\x1B[0m" << endl;
                morgage();
            }
            checkOwnership(currentTurn);
        }
    }
}

void Game::banish(int currentTurn)
{
    cout << setw(50) << "\x1B[92m" << "God has entered the game" << endl;
    cout << "\x1B[91m" << "[Mr.Truong] " << "\x1B[0m" << "Your have entered a property location that you do not own!" << endl;
    cout << "\x1B[91m" << "[Mr.Truong] " << "\x1B[0m" << "Under the 18 U.S.C § 1028. I charge you with Fraud for attempted connection with identification documents and authentication features." << endl;
    cout << "\x1B[91m" << "[Mr.Truong] " << "\x1B[0m" << "Your are herby stripped of your player rights, forgotten and banned from monopoly!" << endl;
}

int Game::getCurrentTurn()
{
    return currentTurn;
}

void Game::playerProfile()
{
    
}