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
<<<<<<< HEAD

=======
    void Ex26(){
        cout << "Programa: Filtro de Matriz" << endl;

        int linhas = 4, colunas = 4;
        int contador = 0;
        vector<vector<int>> matriz(linhas, vector<int>(colunas, 0));

        for (int i = 0; i < linhas; i++)
        {
            for (int j = 0; j < colunas; j++)
            {
                cout << "Entre com um Valor: "; cin >> matriz[i][j];
            }
            
        }
        cout << " Os numeros Maiores de 10 na Matriz Sao: ";
        for (int i = 0; i < matriz.size(); i++)
        {
            for (int j = 0; j < matriz[i].size(); j++)
            {
                if(matriz[i][j]> 10)
                {
                    cout << matriz[i][j]; 
                    contador++;
                    (j == matriz[i].size() - 1)? cout << "." << endl : cout << ", ";
                }
            }
        }
        cout << "No Total foram: " << contador << " valores" << endl;
    }

    void Ex51(){
        cout << "Programa: Verificador de Ordenacao Crescente" << endl;

        vector<int> vetor;
        int entrada;
        bool ordenado = true;

        for (int i = 0; i < 10; i++)
        {
            cout << "Entre com o " << i+1 << ".o Valor: "; cin >> entrada; 
            vetor.push_back(entrada); 
        }
            
        for(int i = 0; i < vetor.size()-1; i++)
        {
            if(vetor[i] > vetor[i+1])
            {
                ordenado = false;
                break;
            }
        }
        (ordenado)? cout << " O vetor esta Ordenado de Forma Crescente!" << endl : cout << "O vetor nao esta Ordenado!" << endl;
    }

    void Ex52(){
        cout << "Programa: Verificador de Ordenacao Crescente" << endl;

        vector<int> vetor;
        int entrada;
        bool ordenado = true;

        for (int i = 0; i < 20; i++)
        {
            cout << "Entre com o " << i+1 << ".o Valor: "; cin >> entrada; 
            vetor.push_back(entrada); 
        }
        
        cout << "Vetor Antes da Ordenacao: ";
        for(int i = 0; i < vetor.size(); i++)
        {
            cout << vetor[i];
            (i == vetor.size()-1)? cout << "." << endl : cout << ", ";
        }

        sort(vetor.begin(), vetor.end());

        cout << "Vetor Apos a Ordenacao: ";
        for(int i = 0; i < vetor.size(); i++)
        {
            cout << vetor[i];
            (i == vetor.size()-1)? cout << "." << endl : cout << ", ";
        }
    }
>>>>>>> 9d75bd0 (update: atualizando matérias)
}
