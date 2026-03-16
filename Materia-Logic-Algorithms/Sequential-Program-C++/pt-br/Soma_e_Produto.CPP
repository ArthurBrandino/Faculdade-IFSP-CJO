//C01EX04O.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, B, C, D, P, S;

    cout << "Programa Soma e Produto" << endl << endl;

    cout << "Entre com o valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <D>: "; cin >> D;
    cin.ignore(80, '\n');

    P = A * C;
    S = B + D;

    cout << "O resultado do produto entre " << A << " e " << C << " e: " << P << endl;
    cout << "O resultado da soma entre " << B << " e " << D << " e: " << S << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
