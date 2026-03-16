//C05EX02E.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int I = 0;

    cout << "Programa Numeros Impares de 0 a 20" << endl << endl;

    while (!(I > 20))
    {
        if(I % 2 != 0)
        {
            cout << I;
            if (I < 19)
                cout << " - ";
        }  
        I++;
    }

    cout << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
