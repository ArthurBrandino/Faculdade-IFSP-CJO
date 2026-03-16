//C02EX03A.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, B, X;

    cout << "Difference Between the Greater and the Smaller Program" << endl << endl;

    cout << "Enter the value of <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of <B>: "; cin >> B;
    cin.ignore(80, '\n');

    if (A > B)
        X = A - B;
    else
        X = B - A;

    cout << "The difference between the values is: " << X << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
