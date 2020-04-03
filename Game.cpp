#include "Game.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
//01001110 01101001 01100011 01100101 00100001 00100001 00100000 01000101 01100001 01110011 01110100 01100101 01110010 00100000 01000101 01100111 01100111 00101100 00100000 01101000 01110101 01101000 00111111 00001101 00001010 00100000 00100000 00100000 01011111 00001101 00001010 00100000 00100111 00100000 00100000 00100000 00100111 00001101 00001010 00100111 00100000 00100000 00100000 00100000 00100000 00100111 00001101 00001010 00100000 00100111 00100000 01011111 00100000 00100111 00001101 00001010 00100000
using namespace std;

Game::Game()
{
    int dice_1 = 0;
    int dice_2 = 0;
    inJail = false;
    string map[22][22];
    //i = row
    for(int i = 0; i < 22; i++)
    {
        // j = column
        for(int j = 0; j < 22; j++)
        {
            if(!((2 <= i && i <= 19) && (2 <= j && j <= 19)))
            {
                if(((j % 2) != 0 && j != 0) && j != 20)
                {
                    map[i][j] = "# |";
                }
                else
                {
                    map[i][j] = " # ";
                }
                if(j == 21)
                {
                    map[i][j] = "#";
                }
                
            }
            else
            {
                map[i][j] = "   ";
            }
            
        }
    }
    
    string concat;
    for(int i = 0; i < 22; i++)
    {
        for(int j = 0; j < 22; j++)
        {
            concat += map[i][j];
        }
        if(((i % 2) == 0) && i != 0)
        {
            cout << " -----" << setw(59) << "-----" << endl;
        }
        cout << concat << endl;
        concat = "";
    }
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
