//C05EX06I.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int ANTERIOR = 1, ATUAL = 0, PROXIMO = 0;

    cout << "Programa Sequencia de Fibonacci" << endl << endl;

    cout << PROXIMO;

    for(int I = 0; I <= 15; I++)
    {
        PROXIMO = ANTERIOR + ATUAL;

         cout << ", " << PROXIMO;

        ANTERIOR = ATUAL;
        ATUAL = PROXIMO;
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
