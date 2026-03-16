#include <iostream>
#include <iomanip>

using namespace std;

struct Alunos
{
    string nome;
    float nota1;
    float nota2;
    float media() 
    {
        return (nota1 + nota2) / 2;
    }
};

const int maxalunos = 10;
int contador = 0;
Alunos aluno[maxalunos];

void continuar() 
{
    cout << "Tecle para continuar..." << endl;
    cin.get();
    cin.ignore(); 
}

void cadastro() 
{   
    
    char repetir;
    do
    {
        system("cls");
        cout << "-------------------" << endl;
        cout << "Cadastro de Alunos" << endl;
        cout << "-------------------" << endl;
            if (contador < maxalunos) 
            {
                cout << "Digite o nome do aluno: ";
                cin >> aluno[contador].nome; 
                cout << "Digite a 1.o nota do aluno: ";
                cin >> aluno[contador].nota1;
                cout << "Digite a 2.o nota do aluno: ";
                cin >> aluno[contador].nota2;
                contador++;
                cout << "Aluno cadastrado com sucesso!" << endl;

                cout << "Deseja cadastrar outro aluno? (S/N): ";
                cin >> repetir;
                repetir = toupper(repetir);
            }
            else
            {
                repetir = 'N';
                cout << "Limite de alunos atingido!" << endl;
            }
                
    } while (repetir == 'S');
    continuar();
}

void cabecalho()
{ 
    cout << left << setw(5)  << "N.o"     
         << setw(20) << "Nome"    
         << setw(10) << "Nota 1"  
         << setw(10) << "Nota 2"  
         << setw(10) << "Media"   
        << endl;
}

void exibir() 
{
    system("cls");
    cout << "-------------------" << endl;
    cout << "   Exibir Alunos" << endl;
    cout << "-------------------" << endl;
    if (contador <= 0)
    {
        cout << "Nenhum aluno cadastrado." << endl;
        continuar();
        return;
    }
    cabecalho();
    for (int i = 0; i < contador; i++) 
    {
        cout << left << setw(5)  << (i + 1) 
             << setw(20) << aluno[i].nome 
             << setw(10) << aluno[i].nota1 
             << setw(10) << aluno[i].nota2 
             << setw(10) << aluno[i].media() 
            << endl;
    }
    continuar();
    return;
}

int main(void) 
{  

    int opcao;
    do
    {
        system("cls");
        cout << "-------------------" << endl;
        cout << "   Menu Principal" << endl;
        cout << "-------------------" << endl;
        cout << endl;

        cout << "Menu de Opcoes:" << endl;
        cout << "1. Cadastrar Aluno" << endl;
        cout << "2. Exibir Aluno" << endl;
        cout << "3. Sair" << endl << endl;

        cout << "Escolha uma opcao: ";
        cin >> opcao;
        cin.ignore(); 

        switch (opcao)
        {
            case 1: cadastro(); break;
            case 2: exibir(); break;
            case 3: cout << "Programa Encerrado!"; break;

            default: cout << "Opcao invalida!" << endl;
        }
    } while (opcao != 5);
    
    return 0;
}
