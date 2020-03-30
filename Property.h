#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
using namespace std;

class Property
{
    private:
        int cost;
        int houseCost;
        //{rent,house1,house2,house3,house4,hotel} <-- rent in the array is for rent when no house/hotel is available
        int rent[6];
        //Suggestion: we add how many buildings are built
        int numBuildings;
        string propertyName;
        string owner;
        
    public:
        string setPropertyName(string propertyName_);
        int setCost(int cost_);
        int setRentAt(int i, int rent_);
        void setOwner(string username_, string propertyName_);
        // void getPropertyName(); <--Need more details on how to obtain property name
        void getCost(string propertyName_);
        void getRent(string propertyName_); //<--We need to determine how many houses * rent
        void getHouseCost(string propertyName_);
        void getOwner(string propertyName_);

};
#endif