#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
using namespace std;

class Property
{
    private:
        string propertyName;
        string owner;
        int cost;
        int houseCost;
        //{rent,house1,house2,house3,house4,hotel} <-- rent in the array is for rent when no house/hotel is available
        int rentArr[6];
        //Suggestion: we add how many buildings are built
        int numBuildings;
        
        
    public:
        //Constructor
        Property();
        
        //Modifiers
        void setCost(int cost_);
        void setRentAt(int i, int rent_);
        void setOwner(string username_, string propertyName_);
        void setPropertyName(string propertyName_);
        
        
        //Accessors
        // void getPropertyName(); <--Need more details on how to obtain property name
        int getCost(string propertyName_);
        int getRent(string propertyName_); //<--We need to determine how many houses * rent
        int getHouseCost(string propertyName_);
        string getOwner(string propertyName_);

};
#endif
