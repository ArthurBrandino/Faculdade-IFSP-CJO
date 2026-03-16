//C03EX03K.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main (void){

    float REAL, DOLLAR, RATE;

    cout << "Dollar to Real Conversion Program" << endl << endl;

    cout << "Enter the Dollar Exchange Rate Value: "; cin >> RATE;
    cin.ignore(80, '\n');

    cout << "Enter the Amount in Dollar to be Converted: "; cin >> DOLLAR;
    cin.ignore(80, '\n');

    REAL = DOLLAR * RATE;
    
    cout << "The Converted Amount to Reais is: " << fixed << setprecision(2) << REAL << " R$" << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
