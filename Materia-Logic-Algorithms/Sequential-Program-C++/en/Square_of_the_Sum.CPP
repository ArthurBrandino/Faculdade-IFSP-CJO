//C03EX03N.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main (void){

    int A, B, C, X;

    cout << "Square of the Sum Program" << endl << endl;

    cout << "Enter the Value of the <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the Value of the <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the Value of the <C>: "; cin >> C;
    cin.ignore(80, '\n');


    X = pow((A + B + C), 2);

    cout << "The Square of the Sum is: " << X << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
