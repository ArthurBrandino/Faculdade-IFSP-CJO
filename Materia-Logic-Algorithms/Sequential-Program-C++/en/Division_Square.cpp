//C03EX03Z.CPP

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void)
{
    float A, B, RESULT; 

    cout << "Division Square Program" << endl << endl;

    cout << "Enter the value of the A: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of the B: "; cin >> B;
    cin.ignore(80, '\n');

    RESULT = pow((A / B), 2);
    
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 
    cout << "*" << setw(20) << " RESULT " << setw(11) << "*" << endl;
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 

    cout << "The Square of the Division is: " << fixed << setprecision(2) << RESULT << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
