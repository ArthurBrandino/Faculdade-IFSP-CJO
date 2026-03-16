//C05EX06B.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, X;

    cout << "Programa Tabuada" << endl << endl;

    cout << "Entre com um numero: "; cin >> A;
    cin.ignore(80, '\n');
    cout << endl;

    for(int I = 0; I <= 10; I++)
    {
        X = A * I;
        cout << A << " X " << I << " = " << X << endl;
    }

    cout << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
