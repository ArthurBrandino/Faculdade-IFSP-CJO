//C01EX04A.cpp

#include <iostream>

using namespace std;

int main(void)
{
    int F, C;

    cout << " Entre com a temperatura em graus Celsius" << endl;
    cin >> C;
    cin.ignore(80, '\n');


    F = C * 9 / 5 + 32;

    cout << " A temperatura informada e " << F << " graus Fahrenheit" << endl;

    cout << "Tecle <Enter> para encerrar..." << endl;
    cin.get();
    return 0;
}
