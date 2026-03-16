//C05EX04I.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int I = 0, ANTERIOR = 1, ATUAL = 0, PROXIMO = 0;

    cout << "Programa Sequencia de Fibonacci" << endl << endl;

    cout << PROXIMO << ", ";

    do
    {
        PROXIMO = ANTERIOR + ATUAL;

         cout << ", " << PROXIMO;

        ANTERIOR = ATUAL;
        ATUAL = PROXIMO;
        I++;
    }while(I <= 15);

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
