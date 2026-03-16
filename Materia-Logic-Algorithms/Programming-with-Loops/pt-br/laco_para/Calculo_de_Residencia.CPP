//C05EX06Q.CPP

//Para o Programa se tornar mais completo irei utilizar Matrizes que se encontra no Cápitulo 6 do livro de lógica

#include <iostream>
#include <iomanip>
#include <cctype>

using namespace std;

int main(void)
{
    int I;
    float* L = new float [10];
    float* C = new float [10];
    float* X = new float [10];
    float T = 0;
    char resp;
    string* nome = new string [10];
    
    cout << "Programa Calculo de um Residencia em m^2" << endl << endl;

    for(I = 0; I < 10; I++)
    {
        cout << "Entre com o Nome do " << I + 1 << ".o comodo: "; cin >> nome[I];
        cin.ignore(80, '\n');
        
        cout << "Entre com a Largura do " << I + 1 << ".o comodo:"; cin >> L[I];
        cin.ignore(80, '\n');

        cout << "Entre com a Comprimento do " << I + 1 << ".o comodo:"; cin >> C[I];
        cin.ignore(80, '\n');

        cout << endl;

        X[I] = L[I] * C[I];

        cout << "Deseja Adicionar mais um comodo? (S/N) "; cin >> resp;
        cin.ignore(80, '\n');

        cout << endl;

        if (I == 9) 
            cout << "Limite de comodos atingido!";

        resp = toupper(resp);
        if(resp == 'N')
            break;
    }

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' '); 
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    for(int Y = 0; Y <= I; Y++)
    {
        cout << "Comodo: "  << fixed << setprecision(2) << nome[Y] << " - Largura: " << L[Y] << " Comprimento: " << C[Y] << " = " << X[Y] << "m^2." << endl << endl;
        T += X[Y];
    }
    cout << "Total de comodos: " << I << endl;
    cout << "A Residencia tem " << fixed << setprecision(2) << T << "m^2" << endl << endl;

    delete[] L;
    delete[] C;
    delete[] X;
    delete[] nome;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
