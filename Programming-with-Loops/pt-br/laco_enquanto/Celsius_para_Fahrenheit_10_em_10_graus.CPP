//C05EX01J.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float F, I = 10;

    cout << "Programa de conversao de Celsius para Fahrenheit de 10 em 10 graus" << endl << endl;

    while (I <= 100)
    {
        F = I * 9/5 + 32;

        cout << fixed << setprecision(2) << I << " graus Celsius equivalem a " << F << " graus Fahrenheit." << endl;

        I += 10;
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
