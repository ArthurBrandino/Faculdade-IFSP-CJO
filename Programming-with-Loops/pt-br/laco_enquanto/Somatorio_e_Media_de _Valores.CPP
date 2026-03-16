//C05EX01M.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int I = 1;
    float X, S = 0, M = 0;

    cout << "Programa Somatorio e Media de 10 Valores" << endl << endl;

    while(I <= 10)
    {
        cout << "Entre com o " << I << " valor: "; cin >> X;
        cin.ignore(80, '\n');

        S += X;
        I++;
    }

    M = S/10;

    cout << "O valor do somatorio e: " << S << endl;
    cout << "O valor da media e: " << M << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
