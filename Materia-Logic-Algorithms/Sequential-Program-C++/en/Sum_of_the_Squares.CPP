//C03EX03M.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main (void){

    int A, B, C, X;

    cout << "Sum of the Squares Program" << endl << endl;

    cout << "Enter the Value of the <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the Value of the <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the Value of the <C>: "; cin >> C;
    cin.ignore(80, '\n');


    X = pow(A, 2) + pow(B, 2) + pow(C, 2);

    cout << "The Sum of the Squares is: " << X << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
