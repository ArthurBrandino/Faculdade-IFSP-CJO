//C01EX04J.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int A, B, X;

    cout << "Entre com o valor <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o valor <B>: "; cin >> B;
    cin.ignore(80, '\n');

    X = pow((A - B), 2);

    cout << "O quadrado da diferenca entre <A> e <B> e: " << X << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
