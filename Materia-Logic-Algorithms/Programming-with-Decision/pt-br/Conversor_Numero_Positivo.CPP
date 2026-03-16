//C02EX03B.CPP

#include <iostream>

using namespace std;

int main(void)
{
    int N;

    cout << "Entre com um valor: "; cin >> N;
    cin.ignore(80, '\n');

    if (N<0)
        N = N * -1;

    cout << " O numero positivo e: " << N << endl;

    cout << "Tecle <Enter> para encerrar ... ";
    cin.get();

    return 0;
}
