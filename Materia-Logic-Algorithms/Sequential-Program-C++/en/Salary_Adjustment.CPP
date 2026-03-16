//C03EX03P.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main (void){

    float SM, PR, NS;

    cout << "Salary Adjustment Calculation Program" << endl << endl;

    cout << "Enter Your Salary Amount: "; cin >> SM;
    cin.ignore(80, '\n');

    cout << "Enter the Adjustment Percentage: "; cin >> PR;
    cin.ignore(80, '\n');

    NS = SM + SM *(PR / 100);

    cout << "The Salary with Adjustment is: " << fixed << setprecision(2) << NS << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
