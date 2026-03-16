//C02EX03F.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int A, B, C, X;

    cout << "Programa Diposicao em Ordem Crescente" << endl << endl;

    cout << "Entre com o Valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    if (A > B) { X = A; A = B; B = X; }
    if (A > C) { X = A; A = C; C = X; }
    if (B > C) { X = B; B = C; C = X; }
    

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << A << " < " << B << " < " << C << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
