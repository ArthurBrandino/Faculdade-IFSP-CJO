//C05EX04A.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int X, I = 15;

    cout << "Programa Quadrado de 15 a 200" << endl << endl;

    do
    {
        X = pow(I, 2);

        cout << X << " - ";

        I++;
    }while (I < 201);

    cout << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
