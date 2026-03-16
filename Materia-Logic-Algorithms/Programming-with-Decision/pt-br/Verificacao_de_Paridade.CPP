//C02EX03J.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X;

    cout << "Programa Verificacao de Paridade" << endl << endl;

    cout << "Entre com o Numero a ser Verificado: "; cin >> X;
    cin.ignore(80, '\n');

    if(X % 2 == 0)
        cout << "O numero " << X << " e Par!" << endl;
    else
        cout << "O numero " << X << " e Impar!" << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
