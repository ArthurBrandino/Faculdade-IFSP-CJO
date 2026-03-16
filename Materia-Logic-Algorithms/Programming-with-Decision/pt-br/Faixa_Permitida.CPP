//C02EX03K.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X;

    cout << "Programa Leitura de Valor Dentro da Faixa Permitida" << endl << endl;

    cout << "< A Faixa Permitida e de 1 ate 9>" << endl;
    cout << "Entre com um Numero: "; cin >> X;
    cin.ignore(80, '\n');

    if(X >= 1 && X <= 9)
        cout << "O numero " << X << " esta na Faixa Permitida!" << endl;
    else
        cout << "O numero " << X << " esta Fora da Faixa Permitida!" << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
