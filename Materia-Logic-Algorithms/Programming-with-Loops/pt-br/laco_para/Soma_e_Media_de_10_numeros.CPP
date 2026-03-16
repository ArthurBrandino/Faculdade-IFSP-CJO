//C05EX06M.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int I;
    float X, S = 0, M;
    
    cout << "Programa Soma e Media de 10 numeros " << endl << endl;

    for(I = 0; I < 10; I++)
    {
        cout << "Entre com o " << I+1 << ".o numero: "; cin >> X;
        cin.ignore(80, '\n');

        S += X;
    }

    M = S / I;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << "Soma = " << S << endl;
    cout << "Media = " << fixed << setprecision(2) << M << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
