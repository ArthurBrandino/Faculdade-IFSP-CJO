//C03EX03S.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void){
    
    float A, B, R1, R2, R3, R4;

    cout << "Basic Four Operations Program" << endl << endl;

    cout << "Enter the value of A: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of B: "; cin >> B;
    cin.ignore(80, '\n');

    R1 = A + B;
    R2 = A - B;
    R3 = A * B;
    R4 = A / B;
    
        
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 
    cout << "*" << setw(20) << " RESULTS " << setw(11) << "*" << endl;
    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 

    cout << " A + B = " << fixed << setprecision(2) << R1 << endl;
    cout << " A - B = " << fixed << setprecision(2) << R2 << endl;
    cout << " A X B = " << fixed << setprecision(2) << R3 << endl;
    cout << " A / B = " << fixed << setprecision(2) << R4 << endl;

    cout << setfill('*') << setw(32) << "" << endl;
    cout << setfill(' '); 

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
