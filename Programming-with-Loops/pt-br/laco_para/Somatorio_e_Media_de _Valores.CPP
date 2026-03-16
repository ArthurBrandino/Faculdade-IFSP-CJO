//C05EX06M.CPP

#include <iostream>

using namespace std;

int main(void)
{
    float X, S = 0, M = 0;

    cout << "Programa Somatorio e Media de 10 Valores" << endl << endl;

    for(int I = 0; I < 10; I++)
    {
        cout << "Entre com o " << I << " valor: "; cin >> X;
        cin.ignore(80, '\n');

        S += X;
    }

    M = S/10;

    cout << "O valor do somatorio e: " << S << endl;
    cout << "O valor da media e: " << M << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
