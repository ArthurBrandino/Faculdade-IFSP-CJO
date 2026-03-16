//C05EX03M.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float X, S = 0, M, i = 0;
    
    cout << "Programa Soma e Media de 10 numeros " << endl << endl;

    do
    {
        cout << "Entre com o " << i+1 << ".o numero: "; cin >> X;
        cin.ignore(80, '\n');

        S += X;
        i++;
    } while(!(i >= 10));

    M = S / i;

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
