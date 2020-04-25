#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    cout << "###############################################################################################" << endl;
    ifstream myfile;
    string line;
    myfile.open("chance.txt");
    while(getline(myfile, line, '\r'))
    {
        cout << line << endl;
    }
    myfile.close();
    cout << "###############################################################################################" << endl;
    return 0;
}