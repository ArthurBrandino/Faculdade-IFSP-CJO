//C05EX01Q.CPP

//Para o Programa se tornar mais completo irei utilizar Matrizes que se encontra no Cápitulo 6 do livro de lógica

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int main(void)
{
    int i = 0, y = 0;
    float* L = new float [10];
    float* C = new float [10];
    float* X = new float [10];
    float T = 0;
    char resp;
    string* nome = new string [10];
    
    cout << "Programa Calculo de uma Residencia em m^2" << endl << endl;

    resp = 'S';
    while(resp == 'S')
    {
        if (i >= 10) {
            cout << "Limite de comodos atingido!\n";
            break;
        }

        cout << "Entre com o Nome do " << i + 1 << ".o comodo: "; cin >> nome[i];
        cin.ignore(80, '\n');
        
        cout << "Entre com a Largura do " << i + 1 << ".o comodo:"; cin >> L[i];
        cin.ignore(80, '\n');

        cout << "Entre com a Comprimento do " << i + 1 << ".o comodo:"; cin >> C[i];
        cin.ignore(80, '\n');

        cout << endl;

        X[i] = L[i] * C[i];
        i++;

        cout << "Deseja Adicionar mais um comodo? (S/N) "; cin >> resp;
        cin.ignore(80, '\n');

        cout << endl;

        resp = toupper(resp);
    }

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    while(y < i)
    {
        cout << "Comodo: "  << fixed << setprecision(2) << nome[y] << " - Largura: " << L[y] << " Comprimento: " << C[y] << " = " << X[y] << "m^2." << endl << endl;
        T += X[y];
        y++;
    }
    cout << "Total de comodos: " << i << endl;
    cout << "A Residencia tem " << fixed << setprecision(2) << T << "m^2" << endl << endl;

    delete[] L;
    delete[] C;
    delete[] X;
    delete[] nome;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
