//C05EX04G.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int X, I = 0;

    cout << "Programa valor das potencias de base 3" << endl << endl;

    do
    {
        X = pow(3, I);

        cout << "3^" << I << " = " << X << endl;

        I++;
    }while(I <= 15);

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
