//C05EX03D.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int X = 0, I=0;

    cout << "Programa Somatorio de 1 ate 500" << endl << endl;

    do
    {
        X += I;

        cout << X << " - ";

        I++;
    }while (!(I > 500));

    cout << endl << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
