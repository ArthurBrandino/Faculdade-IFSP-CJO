//C05EX6K.CPP

#include <iostream>

using namespace std;

int main(void)
{
    unsigned long long X = 1, S = 0;

    cout << "Programa do somatorio do numero de graos que se pode obter num tabuleiro de xadrez" << endl << endl;

    for(int I = 0; I < 64; I++)
    {
        S += X;
        X *= 2;
    }

    cout << "A o somatorio do numero de graos que se pode obter num tabuleiro de xadrez e " << S;

    cout << endl;
    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
