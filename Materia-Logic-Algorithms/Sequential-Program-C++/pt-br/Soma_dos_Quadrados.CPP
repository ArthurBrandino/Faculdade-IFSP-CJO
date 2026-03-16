//C01EX04M.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int A, B, C, X;

    cout << "Entre com o valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    X = pow(A, 2) + pow(B, 2) + pow(C, 2);

    cout << "O resultado: " << X << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
