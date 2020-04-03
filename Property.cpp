#include "Property.h"
#include "Game.h"
#include <iostream>

using namespace std;

Property::Property()
{
    int cost = 0;
    int houseCost = 0;
    for(int i = 0; i < 6; i++)
    {
        rentArr[i] = 0;
    }
    int numBuildings = 0;
    string owner = "none";
}

void Property::setCost(int cost_)
{
    cost = cost_;
}

void Property::setRentAt(int i, int rent_)
{
    if(0 <= i && 0 < 6)
    {
        cout << "[Error -- setRentAt] Specified index is out of bounds" << endl;
    }
    else
    {
        rentArr[i] = rent_;
    }
}

// We may have an issue how will we address whether the Owner exist for a particular property
// I'll leave this issue out for now
void Property::setOwner(string username_, string propertyName_)
{
    owner = username_;
}

void Property::setPropertyName(string propertyName_)
{
    propertyName = propertyName_;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//Accessors Section
//Error we need to search for property at users location or a certain property
int Property::getCost(string propertyName_)
{
    return cost;
}

// void Property::getRent(string propertyName_)

// void Property::getHouseCost(string propertyName_)

// void Property::getOwner(string propertyName_)

// void Property::

