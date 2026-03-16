//C05EX02R.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
   int X = 0, maior, menor, i = 0;
    
    cout << "Programa Maior e Menor Numero" << endl;
    cout << "* Entre com um numero negativo para encerrar a leitura dos valores *" << endl << endl;

    while(!(X < 0))
    {
        cout << "Entre o " << i + 1 << ".o valor: "; cin >> X;
        cin.ignore(80, '\n');

        if (i == 0)
            maior = menor = X;

        if (X >= 0)
        {
            if(X > maior)
                maior = X;
            else
            {
                if(X < menor)
                    menor = X;
            }
        }

        i++;
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
