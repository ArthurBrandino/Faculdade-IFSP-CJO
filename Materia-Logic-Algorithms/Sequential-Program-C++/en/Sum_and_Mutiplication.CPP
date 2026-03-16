//C03EX03G.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main (void){

    int A, B, C, D, X1, X2, X3, X4, X5, X6, Y1, Y2, Y3, Y4, Y5, Y6;

    cout << "Sum and Mutiplication Program" << endl << endl;

    cout << "Enter the value of A: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of B: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the value of C: "; cin >> C;
    cin.ignore(80, '\n');

    cout << "Enter the value of D: "; cin >> D;
    cin.ignore(80, '\n');

    X1 = A + B;
    X2 = A + C;
    X3 = A + D;
    X4 = B + C;
    X5 = B + D;
    X6 = C + D;

    Y1 = A * B;
    Y2 = A * C;
    Y3 = A * D;
    Y4 = B * C;
    Y5 = B * D;
    Y6 = C * D;

    
    cout << setfill('*') << setw(20) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(9) << "SUM" << setw(9) << " *" << endl;
    cout << setfill('*') << setw(20) << "" << endl;
    cout << setfill(' ');

    cout << "* " << setw(3) << A << " + " << setw(3) << B << " = " << setw(4) << X1 << " *" << endl;
    cout << "* " << setw(3) << A << " + " << setw(3) << C << " = " << setw(4) << X2 << " *" << endl;
    cout << "* " << setw(3) << A << " + " << setw(3) << D << " = " << setw(4) << X3 << " *" << endl;
    cout << "* " << setw(3) << B << " + " << setw(3) << C << " = " << setw(4) << X4 << " *" << endl;
    cout << "* " << setw(3) << B << " + " << setw(3) << D << " = " << setw(4) << X5 << " *" << endl;
    cout << "* " << setw(3) << C << " + " << setw(3) << D << " = " << setw(4) << X6 << " *" << endl;

 
    cout << setfill('*') << setw(20) << "" << endl;
    cout << setfill(' ');


    cout << setfill('*') << setw(20) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "MULTIPLICATION" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(20) << "" << endl;
    cout << setfill(' ');

    cout << "* " << setw(3) << A << " x " << setw(3) << B << " = " << setw(4) << Y1 << " *" << endl;
    cout << "* " << setw(3) << A << " x " << setw(3) << C << " = " << setw(4) << Y2 << " *" << endl;
    cout << "* " << setw(3) << A << " x " << setw(3) << D << " = " << setw(4) << Y3 << " *" << endl;
    cout << "* " << setw(3) << B << " x " << setw(3) << C << " = " << setw(4) << Y4 << " *" << endl;
    cout << "* " << setw(3) << B << " x " << setw(3) << D << " = " << setw(4) << Y5 << " *" << endl;
    cout << "* " << setw(3) << C << " x " << setw(3) << D << " = " << setw(4) << Y6 << " *" << endl;

    cout << setfill('*') << setw(20) << "" << endl;
    cout << setfill(' ') << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
