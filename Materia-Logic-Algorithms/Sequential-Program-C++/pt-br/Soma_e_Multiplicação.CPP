//C01EX04G.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, B, C, D, X1, X2, X3, X4, X5, X6, Y1, Y2, Y3, Y4, Y5, Y6;

    cout << "Programa Soma e Mutiplicacao" << endl << endl;

    cout <<  "Entre com o valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout <<  "Entre com o valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout <<  "Entre com o valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout <<  "Entre com o valor de <D>: "; cin >> D;
    cin.ignore(80, '\n');

    X1 = A + B;
    X2 = A + C;
    X3 = A + D;
    X4 = B + C;
    X5 = B + D;
    X6 = C + D;

    Y1 = A * B;
    Y2 = A * C;
    Y3 = A * D;
    Y4 = B * C;
    Y5 = B * D;
    Y6 = C * D;

    cout << A << " + " << B << " = " << X1 << endl;
    cout << A << " + " << C << " = " << X2 << endl;
    cout << A << " + " << D << " = " << X3 << endl;
    cout << B << " + " << C << " = " << X4 << endl;
    cout << B << " + " << D << " = " << X5 << endl;
    cout << C << " + " << D << " = " << X6 << endl << endl;

    cout << A << " X " << B << " = " << Y1 << endl;
    cout << A << " X " << C << " = " << Y2 << endl;
    cout << A << " X " << D << " = " << Y3 << endl;
    cout << B << " X " << C << " = " << Y4 << endl;
    cout << B << " X " << D << " = " << Y5 << endl;
    cout << C << " X " << D << " = " << Y6 << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
