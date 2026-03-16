//C02EX03K.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X;

    cout << "Allowed Range Value Program" << endl << endl;

    cout << "< The Allowed Range is from 1 to 9 >" << endl;
    cout << "Enter a Number: "; cin >> X;
    cin.ignore(80, '\n');

    if (X >= 1 && X <= 9)
        cout << "The number " << X << " is within the Allowed Range!" << endl;
    else
        cout << "The number " << X << " is Outside the Allowed Range!" << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
