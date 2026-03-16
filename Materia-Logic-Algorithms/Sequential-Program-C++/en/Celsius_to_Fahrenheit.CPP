//C03EX03A.CPP

#include <iostream>
using namespace std;

int main (void){
    int C, F;

    cout << "Celsius to Fahrenheit Conversion Program" << endl << endl;

    cout << "Enter the Temperature in Degrees Celsius: "; cin >> C;
    cin.ignore(80, '\n');

    F = (9 * C + 160)/5;

    cout << "The Temperature in Degrees Fahrenheit is: " << F << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
