// C01EX04B.cpp

#include <iostream>

using namespace std;

int main(void)
{
    int C, F;

    cout << "Entre com a temperatura em graus Fahrenheit: ";
    cin >> F;
    cin.ignore(80, '\n');

    C = ((F-32)*5)/9;

    cout << "A temperatura informada e " << C << " graus Celsius." << endl;


    cout << "Tecle <Enter> para encerrar..." << endl;
    cin.get();
    return 0;
}
