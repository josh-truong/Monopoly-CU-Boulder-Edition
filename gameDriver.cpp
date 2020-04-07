//Note this is a public driver, if you want to test your own code, then create your own driver and call the neccessary files
//This is the brains of the program don't f*** this one up
#include <iostream>
#include "Game.h"
#include "Player.h"
using namespace std;

string toupper(string name) //A function to turn the string entered into all capital leters
{
    int length = name.length(); //Obtains the length of the string
    string newname;
    for(int i = 0; i < length; i++) //Cycles through all of the characters of the entered string.
    {
        if(name[i] >= 97 && name[i] <= 122) //Checks if characher is a lowercase letter using ascii values.
        {
            char newchar = name[i] - 32; //Obtains its capital leter equivalent.
            newname = newname + newchar;
        }
        else
        {
            newname = newname + name[i];
        }
    }
    return newname;
}

int main()
{
    Game monopoly;
    bool successfulRead = monopoly.readPlayers();
    // monopoly.readProperty();
    if(!successfulRead)
    {
        successfulRead = monopoly.readPlayers();
    }
    cout << "Welcome to a Game of Monopoly!" <<endl;
    cout << "Theme: CU Boudler" << endl;
    cout << "Solgan: The only place in Boulder where you can get rich!" << endl;
    monopoly.move(0);
    // monopoly.getPropertyInfo(0);
    return 0;
}
