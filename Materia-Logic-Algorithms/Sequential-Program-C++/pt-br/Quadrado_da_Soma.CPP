//C01EX04N.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int A, B, C, X;

    cout << "Programa Quadrado da Soma" << endl << endl;

    cout << "Entre com o valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    X = pow((A + B + C), 2);

    cout << "O resultado do quadrado da soma de  <A>, <B> e <C> e: " << X << endl << endl;



    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}

