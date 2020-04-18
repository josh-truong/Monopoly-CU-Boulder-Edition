#ifndef PROPERTY_H
#define PROPERTY_H

#include <iostream>
using namespace std;

class Property
{
    private:
        //Variable for all properties
        int propertyLocation;
        string propertyName;
        
        //Variable for only colored properties
        string owner;
        int propertyCost;
        int buildingCost;
        //{rent,house1,house2,house3,house4,hotel} <-- rent in the array is for rent when no house/hotel is available
        //For railroads {1 railRoad, 2 railRoad, 3 railRoad, 4 railRoad}
        int rentArr[6];
        //Suggestion: we add how many buildings are built
        string color;
        int numBuildings;
        bool morgage;
        
        //Variables for railroads
        
        
        
    public:
        //Constructor
        Property();
        
        // //Modifiers
        void setPropertyLocation(int propertyLocation_);
        void setPropertyName(string propertyName_);
        void setOwner(string username_);
        void setPropertyCost(int propertyCost_);
        void setBuildingCost(int buildingCost_);
        void setRentAt(int i, int rent_);
        void setColor(string color);
        void setNumBuildings(int numBuildings_);
        void setMorgage_True();
        
        // //Accessors
        int getPropertyLocation();
        string getPropertyName(); //<--Need more details on how to obtain property name
        string getOwner();
        int getPropertyCost();
        int getBuildingCost();
        void getListOfRentCP(); //Colored Properties
        void getListOfRentTransport(); //Transport Properties
        int getRent(); //<--We need to determine how many houses * rent
        string getColor();
        int getNumBuildings();
        bool getMorgage_Status();
};
#endif
