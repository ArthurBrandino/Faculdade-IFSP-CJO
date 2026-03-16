//C03EX03U.CPP

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void)
{
    float METER, FEET; 

    cout << "Feet to Meters Conversion Program" << endl << endl;

    cout << "Enter the Length in Feet: "; cin >> FEET;
    cin.ignore(80, '\n');

    METER = FEET * 0.3048;
    
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 
    cout << "*" << setw(20) << " RESULT " << setw(11) << "*" << endl;
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 

    cout << "The feet to meters conversion is " << fixed << setprecision(2) << METER << "m ." << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
