//C05EX06F.CPP

#include <iostream>

using namespace std;

int main(void)
{
    cout << "Programa Numeros Divisiveis por 4 menores de 200" << endl << endl;

    for(int I = 0; I < 200; I++)
    {
        if (I % 4 == 0)
        {
            cout << I;
            if (I + 4 < 200) 
                cout << " - ";
        }
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
