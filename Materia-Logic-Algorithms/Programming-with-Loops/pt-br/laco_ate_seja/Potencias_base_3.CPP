//C05EX02G.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int X, I=0;

    cout << "Programa valor das potencias de base 3" << endl << endl;

    while(!(I > 15))
    {
        X = pow(3, I);

        cout << X << endl;

        I++;
    }

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
