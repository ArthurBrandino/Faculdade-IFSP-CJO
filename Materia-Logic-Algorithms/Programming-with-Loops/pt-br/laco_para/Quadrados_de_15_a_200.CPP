//C05EX06A.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int X;
    cout << "Programa Quadrado de 15 a 200" << endl << endl;

    for(int I = 15; I < 201; I++)
    {
        X = pow(I, 2);

        cout << X;
        if(I != 200) 
          cout << " - ";
    }

    cout << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
