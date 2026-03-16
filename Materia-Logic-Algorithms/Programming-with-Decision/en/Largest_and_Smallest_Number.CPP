//C02EX03I.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int A, B, C, D, E, X, Y;

    cout << "Largest and Smallest Number Program" << endl << endl;

    cout << "Enter the value of <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the value of <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << "Enter the value of <D>: "; cin >> D;
    cin.ignore(80, '\n');

    cout << "Enter the value of <E>: "; cin >> E;
    cin.ignore(80, '\n');

    X = A;
    Y = A;

    if (B > X) X = B;
    if (C > X) X = C;
    if (D > X) X = D;
    if (E > X) X = E;

    if (B < Y) Y = B;
    if (C < Y) Y = C;
    if (D < Y) Y = D;
    if (E < Y) Y = E;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Result" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << "Largest Number: " << X << endl;
    cout << "Smallest Number: " << Y << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
