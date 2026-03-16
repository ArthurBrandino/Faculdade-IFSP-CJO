//C05EX02C.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X = 0, I = 0;

    cout << "Programa Soma dos Primeiros 100 Numeros" << endl << endl;

    while (!(I > 100))
    {
        X += I;

        if(I != 100)
            cout << X << " - ";

        I++;
    }

    cout << "." << endl << endl;
    cout << "Soma total = " << X << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
