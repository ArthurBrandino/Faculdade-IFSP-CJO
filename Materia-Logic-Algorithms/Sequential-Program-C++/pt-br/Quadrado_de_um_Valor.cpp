//C01EX04I.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    int x;

    cout << "Entre com um valor: "; cin >> x;
    cin.ignore(80, '\n');

    cout << "O quadrado do valor e: " << pow(x, 2) << endl;

    cout << "Tecle <Enter> para encerrar";
    cin.get();

    return 0;
}
