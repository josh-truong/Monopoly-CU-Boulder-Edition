#include "Player.h"
#include <iostream>

using namespace std;

//PLAYER CLASS IS FINISHED

Player::Player()
{
    balance = 1500;
    boardlocation = 0;
    playerPos_x = 0;
    playerPos_y = 0;
    bankrupt = false;
}

void Player::setName(string playerName_)
{
    playerName = playerName_;
    // cout << "playerName: " << playerName << endl;
}

void Player::setBalance(int balance_)
{
    balance = balance_;
    // cout << "balance: " << balance << endl;
}

void Player::setBoardLocation(int boardlocation_)
{
    boardlocation = boardlocation_ % 40;
}

void Player::setPlayerPos(int x, int y)
{
    playerPos_x = x;
    playerPos_y = y;
    // cout << "playerPos_x: " << playerPos_x << endl;
    // cout << "playerPos_y: " << playerPos_y << endl;
}

void Player::setPlayerChar(string playerChar_)
{
    playerChar = playerChar_;
    // cout << "playerChar: " << playerChar << endl;
}

void Player::setBankruptStatusTrue()
{
    bankrupt = true;
}

string Player::getName() const
{
    return playerName;
}

int Player::getBoardLocation()
{
    return boardlocation;
}

string Player::getPlayerChar() const
{
    return playerChar;
}

int Player::getBalance() const
{
    return balance;
}

int Player::getPlayerPos_x() const
{
    return playerPos_x;
}

int Player::getPlayerPos_y() const
{
    return playerPos_y;
}

bool Player::getStatus() const
{
    return bankrupt;
}
