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

Game::Game()
{
    dice_1 = 0;
    dice_2 = 0;
    inJail = false;
    
    cout << "How many players? (2-4): " << endl;
    cin >> numPlayers;
    
    //Initialized Tabula Rasa Board
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            for(int k = 0; k < 2; k++)
            {
                for(int l = 0; l < 2; l++)
                {
                    if(!((1 <= i && i <= 9) && (1 <= j && j <= 9)))
                    {
                        map[i][j][k][l] = '#';
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
                    map[i][j][k][l] += ' ';
                }
            }
        }
    }
}

void Game::move()
{
    //This is where we will update players position
    int i = 10;
    int j = 10;
    int k = 0;
    int l = 0;
    string playerPiece = "*";
    if(!((1 <= i && i <= 9) && (1 <= j && j <= 9)))
    {
        map[i][j][k][l] = playerPiece;
    }
    else
    {
        map[i][j][k][l] = ' ';
    }
    if(((l % 2) != 0) && !((1 <= i && i <= 9) && (1 <= j && j <= 9)) && j != 10)
    {
        map[i][j][k][l] += "|";
    }
    else
    {
        map[i][j][k][l] += " ";
    }
    map[i][j][k][l] += " ";
    display_MapAndPlayer();
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

void Game::readPlayers()
{
    ifstream readPlayerFile;
    string x_pos, y_pos, playerChar_, playerName;
    readPlayerFile.open("player.csv");
    for(int i = 0; i <= numPlayers; i++)
    {
        getline(readPlayerFile, x_pos, ',');
        getline(readPlayerFile, y_pos, ',');
        getline(readPlayerFile, playerChar_, ',');
        if(i != 0)
        {
            cout << "(" << (i - 1) << ") Enter a player name: " << endl;
            cin >> playerName;
            
            player[i - 1].setName(playerName);
            player[i - 1].setPlayerChar(playerChar_);
            player[i - 1].setPlayerPos(stoi(x_pos), stoi(y_pos));
        }
    }
    // for(int i = 0; i < numPlayers; i++)
    // {
    //     cout << player[i].getName() << " (" << player[i].getPlayerChar() << ")" << endl;
    //     cout << "Balance: " << player[i].getBalance() << endl;
    //     cout << "(" << player[i].getPlayerPos_x() << ", " << player[i].getPlayerPos_y() << ")" << endl;
    // }
    readPlayerFile.close();
}

void Game::readProperty()
{
    
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
