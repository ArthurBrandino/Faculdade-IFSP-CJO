//C05EX03J.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int F, I = 10;

    cout << "Programa de conversao de Celsius para Fahrenheit de 10 em 10 graus" << endl << endl;

    do
    {
        F = I * 9/5 + 32;

        cout << I << " graus Celsius = " << F << " graus Fahrenheit" << endl;

        I += 10;
    }while (!(I > 100));

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
