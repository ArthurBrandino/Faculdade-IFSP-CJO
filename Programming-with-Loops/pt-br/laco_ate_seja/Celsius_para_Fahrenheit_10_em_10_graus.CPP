//C05EX02J.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int F, I = 10;

    cout << "Programa de conversao de Celsius para Fahrenheit de 10 em 10 graus" << endl << endl;

    while (!(I > 100))
    {
        F = I * 9/5 + 32;

        cout << I << " graus Celsius = " << F << " graus Fahrenheit" << endl;

        I = I + 10;
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
