//C05EX06C.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X = 0;

    cout << "Programa Soma dos Primeiros 100 Numeros" << endl << endl;

    for(int I = 0; I <= 100; I++)
    {
        X += I;

        if(I != 100)
            cout << X << " - ";
    }

    cout << "." << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
