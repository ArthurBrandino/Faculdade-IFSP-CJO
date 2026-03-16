//C05EX06G.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int X;

    cout << "Programa valor das potencias de base 3" << endl << endl;

    for(int I = 0; I <= 15; I++)
    {
        X = pow(3, I);

        cout << "3^" << I << " = " << X << endl;
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
