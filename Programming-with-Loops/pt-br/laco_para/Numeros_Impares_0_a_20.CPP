//C05EX06E.CPP

#include <iostream>

using namespace std;

int main(void)
{
    cout << "Programa Numeros Impares de 0 a 20" << endl << endl;

    for(int I = 0; I <= 20; I++)
    {
        if(I % 2 != 0)
        {
            cout << I;
            if(I < 19)
                cout<< " - ";
        }

    }

    cout << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
