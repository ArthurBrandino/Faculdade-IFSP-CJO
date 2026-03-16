//C05EX02A.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int X, I = 15;

    cout << "Programa Quadrado de 15 a 200" << endl << endl;

    while (!(I >= 201))
    {
        X = pow(I, 2);

        cout << I << "^2 = " << X << endl;

        I++;
    }

    cout << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
