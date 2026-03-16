// C01EX4C.CPP

#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
    const float PI = 3.14159;
    float VOLUME, R, ALTURA;

    cout << "Entre com o raio da lata: "; cin >> R;
    cin.ignore(80, '\n');

    cout << "Entre com a altura da lata: "; cin >> ALTURA;
    cin.ignore(80, '\n');

    VOLUME = PI * pow(R, 2) * ALTURA;

    cout << "O volume da lata e " << VOLUME << endl;


    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
