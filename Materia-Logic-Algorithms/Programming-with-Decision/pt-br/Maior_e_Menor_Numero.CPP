//C02EX03I.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int A, B, C, D, E, X, Y;

    cout << "Programa Maior e Menor Numero" << endl << endl;

    cout << "Entre com o Valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <D>: "; cin >> D;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <E>: "; cin >> E;
    cin.ignore(80, '\n');

    X = A;
    Y = A; 

    if (B > X) X = B;
    if (C > X) X = C;
    if (D > X) X = D;
    if (E > X) X = E;

    if (B < Y) Y = B;
    if (C < Y) Y = C;
    if (D < Y) Y = D;
    if (E < Y) Y = E;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << "Maior Numero: " << X << endl;
    cout << "Menor Numero: " << Y << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
