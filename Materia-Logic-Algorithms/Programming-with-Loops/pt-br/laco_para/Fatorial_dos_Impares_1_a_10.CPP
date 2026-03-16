//C05EX06O.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int FAT = 1;
    
    cout << "Programa Fatorial de Numeros Impares de 1 a 10 " << endl << endl;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    for(int X = 1; X <= 10; X++)
    {
        if(X % 2 != 0)
        {
            FAT = 1;
            cout << X << "! = ";
            for(int I = 1; I <= X; I++)
            {
                FAT = FAT * I;
                if(I <= X-1)
                    cout << I << " X ";
                else
                    cout << I << " = ";

            }
            cout << FAT << endl << endl;
        }
    }

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
