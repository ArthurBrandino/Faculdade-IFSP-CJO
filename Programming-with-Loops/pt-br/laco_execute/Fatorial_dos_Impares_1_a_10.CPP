//C05EX04O.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int X = 1, FAT = 1, i = 0;
    
    cout << "Programa Fatorial de Numeros Impares de 1 a 10 " << endl << endl;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    do
    {
        if(X % 2 != 0)
        {
            FAT = 1;
            i = 1;
            cout << X << "! = ";
            while(i<=X)
            {
                FAT = FAT * i;
                if(i<= X-1)
                    cout << i << " X ";
                else
                    cout << i << " = ";
                i++;
            }
            cout << FAT << endl << endl;
        }
        
        X++;
    } while(X <= 10);

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
