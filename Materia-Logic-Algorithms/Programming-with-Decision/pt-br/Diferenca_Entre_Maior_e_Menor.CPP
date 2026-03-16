//C02EX03A.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, B, X;

    cout << "Programa Diferenca Entre o Maior e o Menor" << endl << endl;

    cout << "Entre com o valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    if (A>B)
        X = A - B;
    else
        X = B - A;

    cout << "A diferenca entre os valores e: " << X << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
