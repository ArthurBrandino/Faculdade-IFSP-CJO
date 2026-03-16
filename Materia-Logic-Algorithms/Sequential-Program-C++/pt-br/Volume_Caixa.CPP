//C01EX4H.CPP

#include <iostream>

using namespace std;

int main(void)
{
    float COMPRIMENTO, ALTURA, LARGURA, VOLUME;

    cout << "Entre com o comprimento: "; cin >> COMPRIMENTO;
    cin.ignore(80,'\n');

    cout << "Entre com a altura : "; cin >> ALTURA;
    cin.ignore(80, '\n');

    cout << "Entre com a largura: "; cin >> LARGURA;
    cin.ignore(80, '\n');

    VOLUME = COMPRIMENTO * LARGURA * ALTURA;

    cout << "O volume da caixa e " << VOLUME << endl;



    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
