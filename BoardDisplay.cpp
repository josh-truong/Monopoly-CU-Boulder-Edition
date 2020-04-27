#include "Game.h"
#include <iostream>
#include <iomanip>
using namespace std; 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::setPiece(int boardLocation, string playerPiece, int currentTurn)
{
    /*
    set a piece on the board. Using the boardlocation to place a piece into the board
    playerPiece must only take in a single character. ex) $,%,*,@,#
    */
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
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::erase(int currentTurn)
{
    string octothrop;
    //Replace and reset Player Previous Location with an octothrop
    octothrop = "#";
    int oldBoardLocation = player[currentTurn - 1].getPreviousBoardLocation();
    setPiece(oldBoardLocation, octothrop, currentTurn);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Move is used to move a player when they roll the dice
void Game::move()
{
    int boardLocation = player[currentTurn - 1].getBoardLocation();
    string playerPiece;
    bool resetPosition = player[currentTurn - 1].getResetLocation_Status();

    for(int i = 1; i <= 2; i++)
    {
        if(resetPosition && (i == 2))
        {
            erase(currentTurn);
        }
        else if (i == 1)
        {
            player[currentTurn - 1].setBoardLocation(boardLocation + dice_1 + dice_2);
            playerPiece = player[currentTurn - 1].getPlayerChar();
            int newBoardLocation = player[currentTurn - 1].getBoardLocation();
            setPiece(newBoardLocation, playerPiece, currentTurn);
        }
    }
    //This is used only once at the beginning of the game
    player[currentTurn - 1].setResetLocation_TRUE();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::display_MapAndPlayer() const
{
    //4d array - This allows for fixed position of character while knowing which player is on which square
        /*arr[i][j][k][l] <-- I and J represent the number of squares in a monopoly board (11 by 11)
            //k and l are the position of each player. This will not be change under any circumstance to change the player position use i and j
        */
    //This is where the map will be displayed
    cout << endl;
    string firstRowConcatOfK, secondRowConcatOfK;
    int topLinecounter = 20;
    int leftLineCounter = 20;
    int rightLineCounter = 30;
    cout << "                                             ";
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
                    if(k == 0)
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
        cout << setw(47) << leftLineCounter << " | " << firstRowConcatOfK << endl << setw(50) << "   | " << secondRowConcatOfK << rightLineCounter << endl;
        leftLineCounter--;
        rightLineCounter++;
        if(0 <= i && i < 10)
        {
            cout << setw(57) << "   ---------" << setw(80) << "---------" << endl;
        }
        firstRowConcatOfK = "";
        secondRowConcatOfK = "";
    }
    
    int bottomLinecounter = 10;
    cout << "                                             ";
    for(int oneLine = 0; oneLine < 11; oneLine++)
    {
        cout << "      " << bottomLinecounter << " "; 
        bottomLinecounter--;
    }
    cout << endl;
    cout << setw(85) << "\x1B[92m" << "DICE 1: " << "\x1B[0m" << dice_1 << "\x1B[92m" << "      DICE 2: " << "\x1B[0m" << dice_2 << endl;
    if(dice_1 == dice_2)
    {
        cout << setw(71) << "\x1B[92m" << "[Mr.Monopoly]" << "\x1B[0m" << " You Rolled A Double. Get a Second Roll!" << endl << endl;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Game::getDisplayStatus()
{
    return player[currentTurn - 1].getDisplayStatus();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Game::setDisplayStatus(int updateStatus)
{
    player[currentTurn - 1].setDisplayStatus(updateStatus);
}