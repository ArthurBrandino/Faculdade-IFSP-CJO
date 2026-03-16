//C02EX03G.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int A, B, C, D;

    cout << "Programa Numeros Divisiveis por 2 e 3" << endl << endl;

    cout << "Entre com o Valor de <A>: "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <B>: "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <D>: "; cin >> D;
    cin.ignore(80, '\n');

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << "Os Numeros Divisiveis por 2 e 3 sao: ";

    if(A % 2 == 0 && A % 3 == 0)
        cout << A << ", ";
    if(B % 2 == 0 && B % 3 == 0)
        cout << B << ", ";
    if(C % 2 == 0 && C % 3 == 0)
        cout << C << ", ";
    if(D % 2 == 0 && D % 3 == 0)
        cout << D;
    cout << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
