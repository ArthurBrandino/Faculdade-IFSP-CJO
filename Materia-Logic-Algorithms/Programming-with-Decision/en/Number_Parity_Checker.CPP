//C02EX03J.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X;

    cout << "Number Parity Checker Program" << endl << endl;

    cout << "Enter the number to be checked: "; cin >> X;
    cin.ignore(80, '\n');

    if (X % 2 == 0)
        cout << "The number " << X << " is Even!" << endl;
    else
        cout << "The number " << X << " is Odd!" << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
