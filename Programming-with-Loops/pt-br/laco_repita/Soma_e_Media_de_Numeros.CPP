//C05EX03N.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float X = 0, S = 0, M;
    int i = 0;
    
    cout << "Programa Soma e Media de Numeros" << endl << endl;
    cout << setfill('*') << setw(60) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(53) << "Para encerrar os calculos insira um numero negativo!" << " *" << endl;
    cout << setfill('*') << setw(60) << "" << endl;
    cout << setfill(' ');

    do
    {
        cout << "Entre com o " << i+1 << ".o numero: "; 
        cin >> X;
        cin.ignore(80, '\n');

        if (X >= 0) 
        {
          S += X;
          i++;
        }
    }while (!(X > 0));

    if (i > 0)
    {
        M = S / i;

        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');

        cout << "Total de Valores Lidos = " << i << endl;
        cout << "Soma = " << S << endl;
        cout << "Media = " << fixed << setprecision(2) << M << endl << endl;
    } 
    else 
      cout << "Nenhum valor positivo foi inserido!" << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
