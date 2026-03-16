//C02EX03G.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int A, B, C, D;

    cout << "Program - Numbers Divisible by 2 and 3" << endl << endl;

    cout << "Enter the value of <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the value of <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << "Enter the value of <D>: "; cin >> D;
    cin.ignore(80, '\n');

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Result" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << "Numbers divisible by 2 and 3 are: ";

    if(A % 2 == 0 && A % 3 == 0)
        cout << A << ", ";
    if(B % 2 == 0 && B % 3 == 0)
        cout << B << ", ";
    if(C % 2 == 0 && C % 3 == 0)
        cout << C << ", ";
    if(D % 2 == 0 && D % 3 == 0)
        cout << D;
    cout << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
