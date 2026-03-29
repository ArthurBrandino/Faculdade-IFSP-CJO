#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <string>

using namespace std;
namespace Revisao2 {
    void Ex01(){
        cout << "Programa: Armazenamento de Numeros Inteiros" << endl;

        int numeros[10];

        for (int i = 0; i < 10; i++)
        {
            cout << "Entre com o " << i+1 << ".o Numero: "; cin >> numeros[i];
        }

        for (int i = 0; i < 10; i++)
            cout << "O " << i+1 << ".o numero registrado foi: " << numeros[i] << endl;
        
    }
}
