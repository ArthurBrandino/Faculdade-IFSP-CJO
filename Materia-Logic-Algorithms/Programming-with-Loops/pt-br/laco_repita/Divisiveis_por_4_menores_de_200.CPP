//C05EX03F.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int I = 0;

    cout << "Programa Numeros Divisiveis por 4 menores de 200" << endl << endl;

    do
    {
        if (I % 4 == 0)
        {
            cout << I;
            if( I != 200)
              cout << " - ";
        }
        I++;
    }while (!(I >= 200));

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
