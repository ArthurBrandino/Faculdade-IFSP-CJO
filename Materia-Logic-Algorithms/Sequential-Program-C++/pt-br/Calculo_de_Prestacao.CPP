//C01EX04E.CPP

#include <iostream>

using namespace std;

int main(void)
{
    float VALOR, TEMPO, PRESTACAO, TAXA;

    cout << "Entre com o valor: "; cin >> VALOR;
    cin.ignore(80, '\n');

    cout << "Entre com a taxa: "; cin >> TAXA;
    cin.ignore(80, '\n');

    cout << "Entre com o intervalo de tempo: "; cin >> TEMPO;
    cin.ignore(80, '\n');

    PRESTACAO = VALOR + (VALOR * (TAXA / 100)* TEMPO);

    cout << "O valor da prestacao e " << PRESTACAO << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
