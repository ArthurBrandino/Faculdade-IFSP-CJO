//C03EX01A.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int X, I = 15;

    cout << "Program Squared of 15 to 200" << endl << endl;

    while (I < 201)
    {
        X = pow(I, 2);

        cout << X << " - ";

        I++;
    }

    cout << endl << endl;

    cout << "Press <Enter> to finish...";
    cin.get();

    return 0;
}
