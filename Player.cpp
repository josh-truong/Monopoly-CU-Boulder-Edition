#include "Player.h"
#include <iostream>

using namespace std;

//PLAYER CLASS IS FINISHED

Player::Player()
{
    balance = 1500;
    playerPos_x = 0;
    playerPos_y = 0;
    bankrupt = false;
}

void Player::setName(string playerName_)
{
    playerName = playerName_;
}

void Player::setBalance(int balance_)
{
    balance = balance_;
}

void Player::setPlayerPos(int x, int y)
{
    playerPos_x = x;
    playerPos_y = y;
    // cout << "playerPos_x: " << playerPos_x << endl;
    // cout << "playerPos_y: " << playerPos_y << endl;
}

void Player::setBankruptStatusTrue()
{
    bankrupt = true;
}

string Player::getName() const
{
    return playerName;
}

int Player::getBalance() const
{
    return balance;
}

bool Player::getStatus() const
{
    return bankrupt;
}
