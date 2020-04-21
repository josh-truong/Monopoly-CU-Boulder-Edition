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

int Game::getAmountofBankruptPlayers();
{
    int answer
    for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getBankruptStatus() == true)
        {
            answer++;
        }
    }
    return answer;
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
                    string company, propertyCost;
                    getline(strm, company, ',');
                    getline(strm, propertyCost, ',');
                    property[propertyLocation_int].setPropertyName(company);
                    property[propertyLocation_int].setPropertyLocation(propertyLocation_int);
                    property[propertyLocation_int].setPropertyCost(stoi(propertyCost));
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


void Game::roll()
{
    srand((unsigned)time(0));
    for(int i = 0; i < 2; i++)
    {
        dice_1 = rand() % 6 + 1;
        dice_2 = rand() % 6 + 1;
    }
    cout << "DICE 1: " << dice_1 << "      DICE 2: " << dice_2 << endl;
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

int Game::getPlayerLocation()
{
    int boardlocation = player[currentTurn - 1].getBoardLocation();
    return boardlocation;
}


void Game::endGame()
{
    /*
    This function will allow the users to end the game whenver they feel like it by typing in quit. This will allow for 
    the users to quit if they wish to but could also allow you to calculate the response if someone wins by setting up
    a condition to activate it in main. It print a message to a text file that will display the results and the winner, 
    along with their balances.
    */

    ofstream victory;
    victory.open("results.txt");
    int largestbalance = 0;
    string winner;
    for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getBankruptStatus() == false)
        {
            largestbalance = player[i].getBalance();
            winner = player[i].getName();
        }
    }
    victory << "The winner is " << winner << " with a balance of " << largestbalance << ". Congratulations on your monopoly." << endl;
    cout << "The winner is " << winner << " with a balance of $" << largestbalance << ". Congratulations on your monopoly." << endl;
}


void Game::tradeWithMoney(int propertyLocation, int deal)
{
    /*
    This function allows the user to offer a trade to another player. It takes the name of the player, the property you want to offer,
    and the amount of money you want to offer. It will then allow the person being offered to decide if they want to accept the offer or not.
    If they accepted the offer, it will transfer the money and exchange the properties.
    */
   string currentOwnerOfProperty = property[propertyLocation].getOwner();
   string potentialOwner = player[currentTurn - 1].getName();
   if(currentOwnerOfProperty == "none" || currentOwnerOfProperty == "Mr.Monopoly (Rich Uncle Pennybags)")
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
void Game::tradeWithProperty(int IwantThis, int IGiveYouThat)
{
    /*
    This function allows the user to offer a trade to another player. It takes the name of the player, the property you want to offer,
    and the amount of money you want to offer. It will then allow the person being offered to decide if they want to accept the offer or not.
    If they accepted the offer, it will transfer the money and exchange the properties.
    */
   string currentOwnerOfProperty = property[IwantThis].getOwner();
   string potentialOwner = player[currentTurn - 1].getName();
   if((currentOwnerOfProperty == "none" || currentOwnerOfProperty == "Mr.Monopoly (Rich Uncle Pennybags)") && (0 <= IwantThis && IwantThis < 40))
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
            cout << "\x1B[92m" << potentialOwner << "\x1B[0m" << " --> " << "\x1B[92m" << currentOwnerOfProperty << "\x1B[0m" << " Will you trade your " << "\x1B[92m" << "[" << IwantThis << "]" << property[IwantThis].getPropertyName() << "\x1B[0m" << " for a " << "\x1B[92m" << "[" << IGiveYouThat << "]" << property[IGiveYouThat].getPropertyName() << "\x1B[0m" << endl;
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
        //WARNING -- We need to create and call an auction property
    }
}

void Game::buyHouse(int propertyLocation)
{
    /*
    This function will allow the user to buy a house for one of their properties. It will obtain the house cost from the property
    array and move the rent array down one position. It will also subtract the house cost from the player's balance.
    */
    string owner = property[propertyLocation].getOwner();
    string color = property[propertyLocation].getColor();
    if(toupper(owner) == toupper(player[currentTurn - 1].getName()) && property[propertyLocation].getNumBuildings() <= 5)
    {
        int counter = 0;
        for(int i = 0; i < 40; i++)
        {
            if(color == property[i].getColor() && owner == property[i].getOwner())
            {
                counter++;
            }
        }
        if(counter == 2 && (color == "purple" || color == "dark blue"))
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() << "?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(toupper(userinput) == "Y")
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
                            if(property[propertyLocation].getNumBuildings() < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            cout << "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(toupper(userinput) == "N")
            {
                cout << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else if(counter == 3)
        {
            cout << "Would you like to buy a house for " << property[propertyLocation].getPropertyName() << "?" << endl;
            cout << "Type Y for yes and N for no" << endl;
            string userinput;
            cin >> userinput;
            if(toupper(userinput) == "Y")
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
                            if(property[propertyLocation].getNumBuildings() < 5)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 1 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 1 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 4)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 2 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 2 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 3)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 3 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 3 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 2)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 4 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 4 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            if(property[propertyLocation].getNumBuildings() < 1)
                            {
                                int amount = player[currentTurn - 1].getBalance();
                                cout << "Transaction Process: " << "\x1B[92m" << "$" << amount << "\x1B[91m" << " - $" << 5 * property[propertyLocation].getBuildingCost() << "\x1B[0m" << endl;
                                amount -= 5 * property[propertyLocation].getBuildingCost();
                                player[currentTurn - 1].setBalance(amount);
                                cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Your Balance After Transaction: " << "\x1B[92m" << "$" << amount << "\x1B[0m" << endl; 
                                repeater = 0;
                                property[propertyLocation].setNumBuildings(property[propertyLocation].getNumBuildings() + 1);
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
                            cout << "Invalid input" << endl;
                        }
                    }
                }
            }
            else if(toupper(userinput) == "N")
            {
                cout << "No houses have been purchased" << endl;
            }
            else
            {
                cout << "Invalid input." << endl;
            }
        }
        else
        {
            cout << "You do not have a monopoly on this property" << endl;
        }
    }
    else
    {
        cout << "You cannot purchase a house for this property." << endl; 
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

void Game::jail()
{
    /*
    This function will move a player directly to jail. It will then set a boolian to true which will remain true until three turns
    pass or the player succeeds in rolling a double. 
    */
    setPiece(10,player[currentTurn - 1].getPlayerChar(), currentTurn);
    erase(currentTurn);
    display_MapAndPlayer();
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
                player[currentTurn - 1].setBoardLocation(0);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition,player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                passGo();
                checkOwnership(currentTurn);
                display_MapAndPlayer();
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
                string user = player[currentTurn - 1].getName();
                int counter = 0;
                for(int i = 0; i < 40; i++)
                {
                    if(user == property[i].getOwner())
                    {
                        counter += property[i].getNumBuildings();
                    }
                }
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 40 * counter;
                player[currentTurn - 1].setBalance(amount);
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
                player[currentTurn - 1].setBoardLocation(0);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition,player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                passGo();
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 2:
            {
                cout << line  << endl;
                player[currentTurn - 1].setBoardLocation(24);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                if(player[currentTurn - 1].getBoardLocation() > 24)
                {
                    passGo();
                }
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 3:
            {
                cout << line  << endl;
                player[currentTurn - 1].setBoardLocation(11);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                if(player[currentTurn - 1].getBoardLocation() > 11)
                {
                    passGo();
                }
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 4:
            {
                cout << line  << endl;
                int playerposition = player[currentTurn - 1].getBoardLocation();
                if(playerposition == 7 || playerposition == 36)
                {
                    player[currentTurn - 1].setBoardLocation(12);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);

                    string owner = property[12].getOwner();
                    if(owner == "none")
                    {
                        buy(12, currentTurn);
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
                    player[currentTurn - 1].setBoardLocation(28);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);

                    string owner = property[28].getOwner();
                    if(owner == "none")
                    {
                        buy(28, currentTurn);
                    }
                    else
                    {
                        int amount = player[currentTurn - 1].getBalance();
                        amount = amount - 10 * (dice_1 + dice_2);
                        player[currentTurn - 1].setBalance(amount);
                    }
                }
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 5:
            {
                cout << line  << endl;
                int playerposition = player[currentTurn - 1].getBoardLocation();
                if(playerposition == 7)
                {
                    player[currentTurn - 1].setBoardLocation(15);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);

                    string owner = property[15].getOwner();
                    if(owner == "none")
                    {
                        buy(15, currentTurn);
                    }
                    else
                    {
                        rent(15, currentTurn);
                    }
                }
                else if(playerposition == 22)
                {
                    player[currentTurn - 1].setBoardLocation(25);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);

                    string owner = property[25].getOwner();
                    if(owner == "none")
                    {
                        int repeater = 1;
                        while(repeater == 1)
                        {
                            buy(25, currentTurn);
                        }
                    }
                    else
                    {
                        rent(25, currentTurn);
                    }
                }
                else if(playerposition == 38)
                {
                    player[currentTurn - 1].setBoardLocation(5);
                    int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                    setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                    erase(currentTurn);

                    string owner = property[5].getOwner();
                    if(owner == "none")
                    {
                        buy(5, currentTurn);
                    }
                    else
                    {
                        rent(5, currentTurn);
                    }
                }
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 6:
            {
                cout << line << endl;
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
                player[currentTurn - 1].setBoardLocation(28);

                int newPlayerPosition = player[currentTurn - 1].getBoardLocation() - 3;
                setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);                
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 9:
            {
                cout << line  << endl;
                jail();
                display_MapAndPlayer();
                break;
            }
            case 10:
            {
                cout << line  << endl;
                string user = player[currentTurn - 1].getName();
                int counter = 0;
                for(int i = 0; i < 40; i++)
                {
                    if(user == property[i].getOwner())
                    {
                        counter += property[i].getNumBuildings();
                    }
                }
                int amount = player[currentTurn - 1].getBalance();
                amount = amount - 25 * counter;
                player[currentTurn - 1].setBalance(amount);
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
                player[currentTurn - 1].setBoardLocation(5);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                if(player[currentTurn - 1].getBoardLocation() > 5)
                {
                    passGo();
                }
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 13:
            {
                cout << line  << endl;
                player[currentTurn - 1].setBoardLocation(39);
                int newPlayerPosition = player[currentTurn - 1].getBoardLocation();
                setPiece(newPlayerPosition, player[currentTurn - 1].getPlayerChar(), currentTurn);
                erase(currentTurn);
                checkOwnership(currentTurn);
                display_MapAndPlayer();
                break;
            }
            case 14:
            {
                cout << line  << endl;
                //Unfortunate Player
                for(int i = 0; i < numPlayers - 1; i++)
                {
                    int amount = player[currentTurn - 1].getBalance();
                    amount = amount - 50;
                    player[currentTurn - 1].setBalance(amount);
                }
                //Lucky Player
                for(int j = 0; j < numPlayers; j++)
                {
                    if(currentTurn - 1 != j)
                    {
                        int amount = player[j].getBalance();
                        amount = amount + 50;
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
        else if(ownership_status != player[currentTurn - 1].getName() && (player[currentTurn - 1].getBoardLocation() == 12 || player[currentTurn - 1].getBoardLocation() == 28))
        {
            waterElectricRent();
        }
    }
}

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
        if((property[i].getOwner() == player[currentTurn - 1].getName()) && (property[i].getMorgage_Status() == false))
        {
            cout << "[" << i << "] " << owned_PropertyName << " | Price: \x1B[92m$" << propertyCost << "\x1B[0m" << " | Morgaged Value: \x1B[91m$" << morgagedCost << "\x1B[0m" << " | Current Rent: \x1B[91m$" << propertyRent << "\x1B[0m" << endl;
            nonMorgaged_property_counter++;
            allProperties++;
        }
        else if((property[i].getOwner() == player[currentTurn - 1].getName()) && (property[i].getMorgage_Status() == true))
        {
            cout << "\x1B[91m" << "[Morgaged Property] [" << i << "] " << owned_PropertyName << "\x1B[0m" << " | Unmortgage Price: " << "\x1B[91m" << "$" << (propertyCost + (propertyCost * 0.1)) << "\x1B[0m" << endl;
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

int Game::listOfOwnedProperties_ByOtherPlayers()
{
    int spyPlayer;
    for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getName() != player[currentTurn - 1].getName())
        {
            cout << "\x1B[92m" << "[" <<  i + 1 << "]" << "\x1B[0m" << player[i].getName() << "      ";
        }
    }
    cout << endl;
    do
    {
        cout << "Which Player do you want to Check? (Enter from a range of 1 to " << numPlayers << "): ";
        cin >> spyPlayer;
    }while(!(1 <= spyPlayer && spyPlayer <= numPlayers));

    int nonMorgaged_property_counter = 0;
    int allProperties = 0;
    cout << "----------Owned Properties----------" << endl;
    for(int i = 0; i < 40; i++)
    {
        string owned_PropertyName = property[i].getPropertyName();
        int propertyRent = property[i].getRent();
        int propertyCost = property[i].getPropertyCost();
        int morgagedCost = propertyCost / 2;
        if((property[i].getOwner() == player[spyPlayer - 1].getName()) && (property[i].getMorgage_Status() == false))
        {
            cout << "[" << i << "] " << owned_PropertyName << " | Price: \x1B[92m$" << propertyCost << "\x1B[0m" << " | Morgaged Value: \x1B[91m$" << morgagedCost << "\x1B[0m" << " | Current Rent: \x1B[91m$" << propertyRent << "\x1B[0m" << endl;
            nonMorgaged_property_counter++;
            allProperties++;
        }
        else if((property[i].getOwner() == player[spyPlayer - 1].getName()) && (property[i].getMorgage_Status() == true))
        {
            cout << "\x1B[91m" << "[Morgaged Property] [" << i << "] " << owned_PropertyName << "\x1B[0m" << " | Unmortgage Price: " << "\x1B[91m" << "$" << (propertyCost + (propertyCost * 0.1)) << "\x1B[0m" << endl;
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
    cout << "\x1B[91m" << "[Mr.T & Mr.K] " << "\x1B[0m" << "Your have entered a property location that you do not own!" << endl;
    cout << "\x1B[91m" << "[Mr.T & Mr.K] " << "\x1B[0m" << "Under the 18 U.S.C § 1028. I charge you with Fraud for attempted connection with identification documents and authentication features." << endl;
    cout << "\x1B[91m" << "[Mr.T & Mr.K] " << "\x1B[0m" << "Your are herby stripped of your player rights, forgotten and banned from monopoly!" << endl;
}

int Game::getCurrentTurn()
{
    return currentTurn;
}

void Game::playerProfile()
{
    cout << "Balance: " << "\x1B[92m" << "$" << player[currentTurn - 1].getBalance() << "\x1B[0m" << endl;
}

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

    while(numBidders > 1)
    {
        for(int i = 0; i < numPlayers; i++)
        {
            if(player[i].getBankruptStatus() == false && playerBidStatus[i] == true)
            {
                cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << " Do I have any more bids?" << endl;
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
                            cout << "Player " << "\x1B[92m" << "[" << player[i].getName() << "] " << "\x1B[0m" << "has bid for " << "\x1B[92m" << "$" << bidPrice << endl;
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
                        for(int j = 0; j < numBidders; j++)
                        {
                            if(playerCurrentBid[j] > highestBid)
                            {
                                highestBid = playerCurrentBid[j];
                                playerWithHighestBid = j;
                            }
                        }
                        if(playerWithHighestBid == i)
                        {
                            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << player[i].getName() << " you are not allowed to leave the auction ground because you are our highest bidder!" << endl;
                            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Miss A Turn." << endl;
                        }
                        else
                        {
                            playerBidStatus[i] = false;
                            numBidders--;
                            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << player[i].getName() << " has withdrawn!" << endl;
                        }
                        break;
                    }
                    default:
                        cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "You've Entered an Invalid Option. Miss A Turn." << endl;
                        break;
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


void Game::bankrupt()
{
    player[currentTurn - 1].setBankruptStatusTrue();
    cout << "\x1B[91m" << player[currentTurn - 1].getName() << " Status is Bankrupt" << "\x1B[0m" << endl;
    int playerIsAlive = 0;
    for(int i = 0; i < numPlayers; i++)
    {
        if(player[i].getBankruptStatus() == false)
        {
            playerIsAlive++;
        }
    }

    cout << "There are " << playerIsAlive << " players left." << endl;

    srand((unsigned)time(0));
    int line;
    for(int i = 0; i < 2; i++)
    {
        line = rand() % 3 + 1;
    }

    switch(line)
    {
        case 1:
        {
            cout << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " Looks like your time has run out!" << endl;
            cout << setw(50) << "\x1B[92m" << "Blucifer has entered the game and took you as his creator (Luis Jiménez)..." << endl;
            cout << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "]" << " has left the game." << "\x1B[0m" << endl;

            break;
        }
        case 2:
        {
            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Looks like you entered an unknown realm and never returned...";
            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << player[currentTurn - 1].getName() << " has left the game.";
            break;
        }
        case 3:
        {
            cout << "\x1B[92m" << "[Mr.Monopoly] " << "\x1B[0m" << "Unbeknownst to any players, you decided to go off into the mountains to live of the land and never returned." << endl;
            cout << "\x1B[92m" << "[" << player[currentTurn - 1].getName() << "] " << "\x1B[0m" << " has left the game." << endl;
            break;
        }
    }
}

bool Game::getBankruptStatus(int currentTurn)
{
    return player[currentTurn - 1].getBankruptStatus();
}
