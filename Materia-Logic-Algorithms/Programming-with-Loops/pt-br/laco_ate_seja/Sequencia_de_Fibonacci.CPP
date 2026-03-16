//C05EX02I.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int I=0, ANTERIOR=1, ATUAL=0, PROXIMO=0;

    cout << "Programa Sequencia de Fibonacci" << endl << endl;

    cout << PROXIMO << ", ";

    while(!(I > 15))
    {
        PROXIMO = ANTERIOR + ATUAL;

        cout << PROXIMO << ", ";

        ANTERIOR = ATUAL;
        ATUAL = PROXIMO;
        I++;
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
