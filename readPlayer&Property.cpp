#include "Game.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
//01001110 01101001 01100011 01100101 00100001 00100001 00100000 01000101 01100001 01110011 01110100 01100101 01110010 00100000 01000101 01100111 01100111 00101100 00100000 01101000 01110101 01101000 00111111 00001101 00001010 00100000 00100000 00100000 01011111 00001101 00001010 00100000 00100111 00100000 00100000 00100000 00100111 00001101 00001010 00100111 00100000 00100000 00100000 00100000 00100000 00100111 00001101 00001010 00100000 00100111 00100000 01011111 00100000 00100111 00001101 00001010 00100000
using namespace std; 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
                getline(strm, playerChar_, '\r');
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
                    player[i - 1].setPlayerChar("\x1B[92m" + playerChar_ + "\x1B[0m");
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
                    property[propertyLocation_int].setOwner("\x1B[93mMr.Monopoly (Rich Uncle Pennybags)\x1B[0m \x1B[31m \n-----THIS PROPERTY CANNOT BE OWNED!----- \x1B[0m");
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