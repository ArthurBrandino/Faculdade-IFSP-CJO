//C05EX06R.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
   int X = 0, maior, menor;
    
    cout << "Programa Maior e Menor Numero" << endl;
    cout << "* Entre com um numero negativo para encerrar a leitura dos valores *" << endl << endl;

    for(int I = 0; ; I++)
    {
        cout << "Entre o " << I + 1 << ".o valor: "; cin >> X;
        cin.ignore(80, '\n');

        if (I == 0)
            maior = menor = X;

        if(X < 0)
            break;
      
        if(X > maior)
            maior = X;
        else
        {
            if(X < menor)
                menor = X;
        }
    }

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << "O maior numero e: " << maior << endl;
    cout << "O menor numero e: " << menor << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
