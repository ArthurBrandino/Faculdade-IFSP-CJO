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
    void Ex02(){
        cout << "Programa: Armazenamento de Numeros Reais" << endl;

        float numeros[10];

        for (int i = 0; i < 10; i++)
        {
            cout << "Entre com o " << i+1 << ".o Numero: "; cin >> numeros[i];
        }

        for (int i = 9; i >= 0; i--)
            cout << "O " << i+1 << ".o numero registrado foi: " << numeros[i] << endl;
        
    }

    void Ex03(){
        cout << "Programa: Armazenamento de Numeros Reais" << endl;

        const int totalNotas =15;
        float notas[totalNotas];
        float somaNotas = 0, media;

        for (int i = 0; i < totalNotas; i++)
        {
            cout << "Entre com o " << i+1 << ".o Nota: "; cin >> notas[i];
            somaNotas += notas[i];
        }

        media = somaNotas/totalNotas;
        cout << fixed << setprecision(2);
        for (int i = 0; i < totalNotas; i++)
            cout << i+1 << ".a Nota: " << notas[i] << endl;
        cout << "A media Adquirida: "  << media << endl;
    }

    void Ex03(){
        cout << "Programa: Armazenamento de Numeros Reais" << endl;

        const int totalNotas =15;
        float notas[totalNotas];
        float somaNotas = 0, media;

        for (int i = 0; i < totalNotas; i++)
        {
            cout << "Entre com o " << i+1 << ".o Nota: "; cin >> notas[i];
            somaNotas += notas[i];
        }

        media = somaNotas/totalNotas;
        cout << fixed << setprecision(2);
        for (int i = 0; i < totalNotas; i++)
            cout << i+1 << ".a Nota: " << notas[i] << endl;
        cout << "A media Adquirida: "  << media << endl;
    }

    void Ex04(){
        cout << "Programa: Armazenamento de Numeros Reais" << endl;

        const int totalNotas =15;
        float notas[totalNotas];
        float somaNotas = 0, media;

        for (int i = 0; i < totalNotas; i++)
        {
            cout << "Entre com o " << i+1 << ".o Nota: "; cin >> notas[i];
            somaNotas += notas[i];
        }

        media = somaNotas/totalNotas;
        cout << fixed << setprecision(2);
        for (int i = 0; i < totalNotas; i++)
            cout << i+1 << ".a Nota: " << notas[i] << endl;
        cout << "A media Adquirida: "  << media << endl;
    }

    void Ex05() {
        const int TOTAL = 20;
        int numeros[TOTAL];
        int pares[TOTAL], impares[TOTAL];
        
        int contaPares = 0;
        int contaImpares = 0;

       for (int i = 0; i < TOTAL; i++) {
            cout << "Digite o " << i + 1 << "o numero: ";
            cin >> numeros[i];

            if (numeros[i] % 2 == 0) {
                pares[contaPares] = numeros[i];
                contaPares++;
            } else {
                impares[contaImpares] = numeros[i];
                contaImpares++;
            }
        }

        cout << "Numeros PARES (" << contaPares << "): ";
        for (int i = 0; i < contaPares; i++) {
            cout << pares[i] << " ";
        }
        cout << endl;
        cout << "Numeros IMPARES (" << contaImpares << "): ";
        for (int i = 0; i < contaImpares; i++) {
            cout << impares[i] << " ";
        }
        cout << endl;
    }

}
