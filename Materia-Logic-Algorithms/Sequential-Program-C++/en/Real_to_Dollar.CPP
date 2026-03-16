//C03EX03L.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main (void){

    float REAL, DOLLAR, RATE;

    cout << "Real to Dollar Conversion Program" << endl << endl;

    cout << "Enter the Dollar Exchange Rate Value: "; cin >> RATE;
    cin.ignore(80, '\n');

    cout << "Enter the Amount in Reais to be Converted: "; cin >> REAL;
    cin.ignore(80, '\n');

    DOLLAR = REAL / RATE;
    
    cout << "The Converted Amount to Dollars is: " << fixed << setprecision(2) << DOLLAR << " U$" << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
