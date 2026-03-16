//C05EX06J.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int F;
    cout << "Programa de conversao de Celsius para Fahrenheit de 10 em 10 graus" << endl << endl;

     for(int I = 10; I <= 100; I += 10)
    {
        F = I * 9/5 + 32;

        cout << I << " graus Celsius = " << F << " graus Fahrenheit" << endl;
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
