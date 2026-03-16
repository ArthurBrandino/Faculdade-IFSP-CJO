//C05EX03E.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int I = 0;

    cout << "Programa Numeros Impares de 0 a 20" << endl << endl;

    do
    {
        if(I % 2 != 0)
        {
            cout << I;
            if (I < 19)
                cout << " - ";
        }  
        I++;
    }while (!(I > 20));

    cout << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
