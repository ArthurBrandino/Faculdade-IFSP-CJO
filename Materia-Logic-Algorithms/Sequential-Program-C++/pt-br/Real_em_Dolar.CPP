//C01EX04K.CPP

#include <iostream>

using namespace std;

int main(void)
{
    double COTACAO, REAL, DOLAR;

    cout << "Programa de conversao de real em dolar" << endl << endl;

    cout << "Entre com o valor da cotacao do dolar: "; cin >> COTACAO;
    cin.ignore(80, '\n');

    cout << "Entre com o valor em reias para ser convertido: "; cin >> REAL;
    cin.ignore(80, '\n');

    DOLAR = REAL / COTACAO;

    cout << "O valor convertido para dolar e " << DOLAR << "U$" << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
