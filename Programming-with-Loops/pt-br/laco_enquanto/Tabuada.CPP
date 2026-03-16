//C05EX01B.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, X, I=0;

    cout << "Programa Tabuada" << endl << endl;

    cout << "Entre com um numero: "; cin >> A;
    cin.ignore(80, '\n');
    cout << endl;

    while (I <= 10)
    {
        X = A * I;
        cout << A << " X " << I << " = " << X << endl;
        I++;
    }

    cout << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
