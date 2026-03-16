//C01EX04P.CPP

#include <iostream>

using namespace std;

int main(void)
{
    float SM, PR, NS;

    cout << "Programa de Calculo de Salario com Reajuste" << endl << endl;


    cout << "Entre com o valor do seu salario: "; cin >> SM;
    cin.ignore(80, '\n');

    cout << "Entre com a porcetagem de reajuste: "; cin >> PR;
    cin.ignore(80, '\n');

    NS =  SM + SM * (PR / 100);

    cout << "O novo salario com reajuste e: " << NS << endl << endl;

    cout << "Tecle <Enter> para encerrar";
    cin.get();

    return 0;
}
