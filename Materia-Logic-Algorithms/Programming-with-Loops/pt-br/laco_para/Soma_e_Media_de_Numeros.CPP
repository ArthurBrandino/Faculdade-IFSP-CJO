//C05EX06N.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int I;
    float S = 0, M, X;
    
    cout << "Programa Soma e Media de Numeros" << endl << endl;
    cout << setfill('*') << setw(60) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(53) << "Para encerrar os calculos insira um numero negativo!" << " *" << endl;
    cout << setfill('*') << setw(60) << "" << endl;
    cout << setfill(' ');

    for(I = 0; ; I++)
    {
        cout << "Entre com o " << I+1 << ".o numero: "; 
        cin >> X;
        cin.ignore(80, '\n');

        if(X < 0)
            break;

        S += X;
    }

    if (I > 0)
    {
        M = S / I;

        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');

        cout << "Total de Valores Lidos = " << I << endl;
        cout << "Soma = " << S << endl;
        cout << "Media = " << fixed << setprecision(2) << M << endl << endl;
    } 
    else
        cout << "Nenhum valor positivo foi inserido!" << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
