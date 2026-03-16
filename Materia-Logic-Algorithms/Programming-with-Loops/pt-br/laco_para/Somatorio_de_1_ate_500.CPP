//C05EX06D.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X = 0;

    cout << "Programa Somatorio de 1 ate 500" << endl << endl;

    for(int I = 0; I <= 500; I++)
    {
        X += I;

        cout << X;
        if(I != 500)
            cout << " - ";
    }

    cout << endl << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
