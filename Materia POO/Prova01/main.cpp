#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    cout << ">> Inicio: Prova P1" << endl << endl;

    string entrada;
    int qntd, temp;
    vector<int> notas;

    cout << "* Informe o total de avaliacoes: "; cin >> qntd;
    cin.ignore();

    cout << "* Informe os valores, separados por espacos: ";
    getline(cin, entrada);

    stringstream ss(entrada);
    while(ss >> temp)   notas.push_back(temp);

    int maiorNota = *max_element(notas.begin(), notas.end());

    cout << "Grafico de Barras" << endl << endl;

    for (int i = maiorNota; i >= 1 ; i--)
    {
        cout << i << " | ";
        for (int j = 0; j < notas.size(); j++)
            (notas[j] >= i) ? cout << " * " : cout << "   ";
        cout << endl;
    }
    cout << "  +";
    for (int j = 0; j < notas.size(); j++) cout << " - ";
    cout << endl;

    cout << "   ";
    for (int j = 0; j < notas.size(); j++) cout << " " << notas[j] << " ";
    cout << endl << endl;

    cout << ">> Fim: Prova P1" << endl;
    return 0;
}