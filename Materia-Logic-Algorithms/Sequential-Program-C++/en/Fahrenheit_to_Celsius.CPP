//C03EX03B.CPP

#include <iostream>

using namespace std;

int main(void){

    int F, C;

    cout << "Fahrenheit to Celsius Conversion Program" << endl << endl;

    cout << "Enter the Temperature in Degrees Fahrenheit: "; cin >> F;
    cin.ignore(80, '\n');

    C = ((F - 32)*5)/9;

    cout << "The Temperature in Degrees Celsius is: " << C << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
