//C05EX03H.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int I = 1, X = 1, B, E;

    cout << "Programa Potencia sem Biblioteca <cmath>" << endl << endl;

    cout << "Entre com a base: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o expoente: "; cin >> E;
    cin.ignore(80, '\n');

    do
    {
        X = X * B;
        I++;
    }while(!(I > E));

    cout << B << "^" << E << " = " << X;

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
