//C05EX03P.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    int i = 50, y = 0;
    float S = 0, M;
    
    cout << "Programa Somatorio e Media dos Numeros Pares de 50 a 70 " << endl << endl;

    do
    {
        if(i % 2 == 0)
        {
            S += i;
            y++;
        }
        i++;
    }while(!(i > 70));

    M = S / y;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    cout << "Somatorio = " << S << endl;
    cout << "Media = " << fixed << setprecision(2) << M << endl << endl;
        
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
