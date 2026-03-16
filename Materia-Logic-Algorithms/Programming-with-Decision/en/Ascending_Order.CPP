//C02EX03F.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int A, B, C, X;

    cout << "Ascending Order Program" << endl << endl;

    cout << "Enter the value of <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the value of <C>: "; cin >> C;
    cin.ignore(80, '\n');

    if (A > B) { X = A; A = B; B = X; }
    if (A > C) { X = A; A = C; C = X; }
    if (B > C) { X = B; B = C; C = X; }

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Result" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << A << " < " << B << " < " << C << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
