// C01EX04F.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int A, B, X;

    cout << "Entre com o valor <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o valor <B>: "; cin >> B;
    cin.ignore(80, '\n');

    X = A;
    A = B;
    B = A;

    cout << "Apos a troca de valores... \n O valor de <A> e " << A;
    cout << " e o valor de <B> e " << B << endl;


    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
