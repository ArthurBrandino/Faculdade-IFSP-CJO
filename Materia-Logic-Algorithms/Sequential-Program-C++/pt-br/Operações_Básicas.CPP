//C01EX4S.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, B, X, Y, Z, W;

    cout << "Entre com o valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    X = A + B;
    Y = A - B;
    Z = A * B;
    W = A / B;

    cout << A << " + " << B << " = " << X << endl;
    cout << A << " - " << B << " = " << Y << endl;
    cout << A << " X " << B << " = " << Z << endl;
    cout << A << " / " << B << " = " << W << endl << endl;



    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
