//C10EX01B

#include <iostream>
#include <iomanip> // formatacao da saida
#include <cctype>   // transforma letra minuscula em maiuscula para verificacoes
#include <limits>


using namespace std;

struct Aluno {
    string nome;
    float n1;
    float n2;
    float m;
    bool aprovado;
};

int limiteAlunos = 0;
Aluno dados[20]; // Vetor de alunos

void continuar(void)
{
    cout << "Tecle <Enter> para continuar...";
    cin.get();
}

void calculos(int J)
{
    dados[J].m = (dados[J].n1 + dados[J].n2)/2; // calculo da media do aluno
    if(dados[J].m >= 5)
        dados[J].aprovado = true;
    else
        dados[J].aprovado = false;
}

void organizar(void)
{
    Aluno trocador;
    
    for(int X = 0;  X <= limiteAlunos; X++)
    {
        for(int Y = X + 1; Y <= limiteAlunos; Y++)
        {
            if(dados[Y].nome < dados[X].nome)
            {
                trocador = dados[X];
                dados[X] = dados[Y];
                dados[Y] = trocador;
            }
        }
    }
}

void cabecalho(void)
{
    cout << left << setw(5)  << "N.o"     
         << setw(20) << "Nome"    
         << setw(10) << "Nota 1"  
         << setw(10) << "Nota 2"  
         << setw(10) << "Media"   
         << setw(15) << "Situacao" << endl;
}

void exibirAluno(int i)
{
    cout << left << setw(5)  << i + 1
         << setw(20) << dados[i].nome
         << setw(10) << fixed << setprecision(2) << dados[i].n1
         << setw(10) << fixed << setprecision(2) << dados[i].n2
         << setw(10) <<  fixed << setprecision(2) <<dados[i].m;

    if (dados[i].aprovado)
        cout << setw(15) << "Aprovado";
    else
        cout << setw(15) << "Reprovado";

    cout << endl << endl;
}


void todos(void)
{
    cabecalho();
    
    for(int contador = 0; contador <= limiteAlunos; contador++)
    {
        cout << left << setw(5) << contador + 1;
        cout << left << setw(20) << dados[contador].nome;
        cout << left << setw(10) << dados[contador].n1;
        cout << left << setw(10) << dados[contador].n2;
        cout << left << setw(10) << dados[contador].m;
        if(dados[contador].aprovado)
            cout << left << setw(15) << " Aprovado";
        else   
            cout << left << setw(15) << "Reprovado";
        cout << endl;
    }
}

void aprovados(void)
{
    cabecalho();

    for(int contador = 0; contador <= limiteAlunos; contador++)
    {
        if(dados[contador].aprovado)
        {
            cout << left << setw(5) << contador + 1;
            cout << left << setw(20) << dados[contador].nome;
            cout << left << setw(10) << dados[contador].n1;
            cout << left << setw(10) << dados[contador].n2;
            cout << left << setw(10) << dados[contador].m;
            cout << left << setw(15) << " Aprovado" << endl;
        }
    }
}

void reprovados(void)
{
    cabecalho();

    for(int contador = 0; contador <= limiteAlunos; contador++)
    {
        if(!dados[contador].aprovado)
        {
            cout << left << setw(5) << contador + 1;
            cout << left << setw(20) << dados[contador].nome;
            cout << left << setw(10) << dados[contador].n1;
            cout << left << setw(10) << dados[contador].n2;
            cout << left << setw(10) << dados[contador].m;
            cout << left << setw(15) << " Reprovado" << endl;
        }
    }
}

void listar(int Req)
{
    if(!dados[limiteAlunos].nome.empty())
    {
        switch(Req)
        {
            case 0: todos(); break;
            case 1: aprovados(); break;
            case 2: reprovados(); break;
            default: cout << "Erro no Programa";
        }
    }
    else
        cout << "Nao ha Alunos Registrados!" << endl;
}

void entraNome(int i)
{
    bool nomeValido = false;

    do
    {
        cout << "Entre com o Nome do Aluno: ";
        getline(cin, dados[i].nome);

        nomeValido = true;

        if (dados[i].nome.empty()) {
            cout << "Nome nao pode ser vazio. Tente novamente." << endl;
            nomeValido = false;
        } else {
            for (char c : dados[i].nome) {
                if (isdigit(c)) {
                    cout << "Nome nao pode conter numeros. Tente novamente." << endl;
                    nomeValido = false;
                    break;
                }
            }
        }

    } while (!nomeValido);
}

void entraNota1(int i)
{
    for(;;)
    {
        cout << "Entre com a Nota 1 do Aluno: ";
        cin >> dados[i].n1;

        if (cin.fail())
        {
            cout << "Nota 1 invalida. Use apenas numeros." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(80, '\n');
            break;
        }
    }
}

void entraNota2(int i)
{
    for(;;)
    {
        cout << "Entre com a Nota 2 do Aluno: ";
        cin >> dados[i].n2;

        if (cin.fail())
        {
            cout << "Nota 2 invalida. Use apenas numeros." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else
        {
            cin.ignore(80, '\n');
            break;
        }
    }
}

//-----------------------------------------------------------------------------------SUBROTINAS MAIORES--------------------------------------------------------------------------------


//------------------------------PAGINA DE ADICAO-------------------------------------------


void adicionar(void)
{
    char resp = 'S';

    while (resp == 'S' && limiteAlunos < 20)
    {
        system("cls"); // Windows
        system("clear"); // Linux

        if(!dados[limiteAlunos].nome.empty())
            limiteAlunos++;

        cout << setfill('*') << setw(21) << "" << endl;
        cout << setfill(' ');
        cout << "* " << setw(3) << "Adicionar Alunos" << setw(3) << " *" << endl;
        cout << setfill('*') << setw(21) << "" << endl;
        cout << setfill(' ') << endl << endl;

        // Entrada de dados
        entraNome(limiteAlunos);
        entraNota1(limiteAlunos);
        entraNota2(limiteAlunos);

        // Cálculo
        calculos(limiteAlunos);
        
        cout << "O Aluno " << dados[limiteAlunos].nome << " foi Adicionado!" << endl;

        // Verifica se ainda pode continuar
        if (limiteAlunos < 20)
        {
            cout << "\nDeseja Adicionar outro Aluno? (S/N): ";
            cin >> resp;
            cin.ignore(80, '\n');
            resp = toupper(resp);
        }
        else
        {
            cout << "Limite de alunos atingido!" << endl;
            break;
        }
    }
    organizar();

    continuar();
}


//--------------------------PAGINA DE EDICAO-----------------------------


void editar(void)
{
    int N, OP;
    bool sair = false;

    do
    {
        cout << setfill('*') << setw(30) << "" << endl;
        cout << setfill(' ');
        cout << "*       Editar Alunos       *" << endl;
        cout << setfill('*') << setw(30) << "" << endl << endl;
        cout << setfill(' ') << endl << endl; 

        listar(0); 

        if(!dados[0].nome.empty())
       {
            cout << "\nEntre com o N.o do Aluno a ser editado:" << endl;
            cout << "Tecle (0) para encerrar" << endl;
            cin >> N;
            cin.ignore(80, '\n');

            // Verificação correta do número do aluno
            if (N > 0 && N <= limiteAlunos + 1)
            {
                sair = false;
                do
                {
                    // Mostra os dados do aluno selecionado
                    cabecalho();
                    exibirAluno(N - 1);

                    // Menu de edição
                    cout << "Tecle (1) para alterar Nome, Nota 1 e Nota 2" << endl;
                    cout << "Tecle (2) para alterar apenas o Nome" << endl;
                    cout << "Tecle (3) para alterar apenas a Nota 1" << endl;
                    cout << "Tecle (4) para alterar apenas a Nota 2" << endl;
                    cout << "Tecle (0) para Cancelar a Operacao" << endl;
                    cout << "Opcao: "; cin >> OP; cin.ignore(80, '\n');

                    switch (OP)
                    {
                    case 0:
                        sair = true;
                        break;

                    case 1:
                        cout << "Entre com o Novo Nome: ";
                        getline(cin, dados[N - 1].nome);
                        cout << "Entre com a Nota 1: ";
                        cin >> dados[N - 1].n1; cin.ignore(80, '\n');
                        cout << "Entre com a Nota 2: ";
                        cin >> dados[N - 1].n2; cin.ignore(80, '\n');
                        break;

                    case 2:
                        cout << "Entre com o Novo Nome: ";
                        getline(cin, dados[N - 1].nome);
                        break;

                    case 3:
                        cout << "Entre com a Nota 1: ";
                        cin >> dados[N - 1].n1; cin.ignore(80, '\n');
                        break;

                    case 4:
                        cout << "Entre com a Nota 2: ";
                        cin >> dados[N - 1].n2; cin.ignore(80, '\n');
                        break;

                    default:
                        cout << "Opcao Invalida!" << endl;
                    }

                    // Recalcula a média e a situação do aluno após alteração
                    if (OP > 0 && OP <= 4)
                        calculos(N - 1);

                } while (!sair);

                organizar(); // Reorganiza os alunos após a edição
            
                
            }
            else if (N != 0)
            {
                cout << "Opcao Invalida!" << endl;
            }
        }
        else
            break;
    }while (N != 0);

    continuar();
}


//---------------------------PAGINA DE EXCLUSAO-----------------------------


void excluir(void)
{
    int N;
    bool sair = false;
    int deletar;

    do
    {
        system("cls"); // Windows
        system("clear"); // Linux
        cout << setfill('*') << setw(30) << "" << endl;
        cout << setfill(' ');
        cout << "*      Excluir Alunos      *" << endl;
        cout << setfill('*') << setw(30) << "" << endl;
        cout << setfill(' ') << endl << endl;

        listar(0); // Mostra a lista de alunos

        if(!dados[0].nome.empty())
        {
            cout << "\nEntre com o N.o do Aluno a ser Excluido: " << endl;
            cout << "Tecle (0) para encerrar" << endl;
            cout << "N.o: "; cin >> N; cin.ignore(80, '\n');
            cout << endl << endl;

            // Verifica se o número está dentro do intervalo válido
            if (N > 0 && N <= limiteAlunos + 1)
            {
                cabecalho();
                exibirAluno(N - 1);

                // Confirmação de exclusão
                do
                {
                    cout << "\nTecle (0) para Cancelar a Operacao" << endl;
                    cout << "Tecle (1) para Deletar o Aluno: " << dados[N - 1].nome << endl;
                    cout << "Opcao: "; cin >> deletar; cin.ignore(80, '\n');
                    cout << endl;

                    switch (deletar)
                    {
                        case 0:
                            sair = true;
                            break;

                        case 1:
                            // "Remove" o aluno limpando os dados
                             // Desloca todos os alunos seguintes para trás
                             for (int i = N - 1; i <= limiteAlunos - 1; i++)
                                dados[i] = dados[i + 1];

                            limiteAlunos--; // Reduz a contagem total 
                        
                            cout << "Aluno excluido com sucesso!" << endl << endl;
                            organizar(); 
                            sair = true;
                            break;

                        default:
                            cout << "Opcao Invalida!" << endl << endl;
                            break;
                    }

                } while (!sair);
            }
            else
            {
                if (N != 0)
                    cout << "Opcao Invalida!" << endl;
            }
        }
        else
            break;	

    } while (N != 0);

    continuar();
}


//------------------------PAGINA DE CADASTRO-------------------------------


void cadastrar(void)
{
    int opcao;
    bool sair; 
    do
    {
        system("cls"); // Windows
        system("clear"); // Linux
        cout << setfill('*') << setw(41) << "" << endl;
        cout << setfill(' ');
        cout << "*           Cadastro de Aluno           *" << endl;
        cout << setfill('*') << setw(41) << "" << endl;
        cout << setfill(' ');

        cout << setfill('*') << setw(41) << "" << endl;
        cout << setfill(' ');
        cout << "*   Tecle (1) para Adicionar Alunos     *" << endl;
        cout << "*   Tecle (2) para Editar Alunos        *" << endl;
        cout << "*   Tecle (3) para Excluir Alunos       *" << endl;
        cout << "*   Tecle (0) para Cancelar a Operacao  *" << endl;
        cout << setfill('*') << setw(41) << "" << endl;
        cout << setfill(' ');
        cout << "Opcao: "; cin >> opcao; cin.ignore(80, '\n');
        
        switch(opcao)
        {
            case 0: sair = true; break;
            case 1: adicionar(); break;
            case 2: editar(); break;
            case 3: excluir(); break;
            
            default: cout << "Opcao Invalida!" << endl;
        }
    } while (!sair);
    

}


//--------------------------PAGINA DE PESQUISA--------------------------


void pesquisa(void)
{
    char resp = 'S';
    string pesq;
    int comeco, meio, fim;
    bool acha;

    while(resp == 'S')
    {
        system("cls"); // Windows
        system("clear"); // Linux
        cout << setfill('*') << setw(30) << "" << endl;
        cout << setfill(' ');
        cout << "*       Pesquisar Alunos       *" << endl;
        cout << setfill('*') << setw(30) << "" << endl << endl;
        cout << setfill(' ');

        cout << "Entre com o Nome do Aluno: "; getline(cin, pesq);

        comeco = 0;
        fim = limiteAlunos;
        acha = false;

        while(comeco <= fim && !acha)
        {
            meio = (comeco + fim)/2;
            
            if(pesq == dados[meio].nome)
                acha = true;
            else
            {
                if(pesq < dados[meio].nome)
                    fim = meio - 1;
                else
                    comeco = meio + 1;
            }
        }
        if(acha)
        {
            cabecalho();
            exibirAluno(meio);
        }
        else
            cout << "Nome: " << pesq << " Nao foi Encontrado no Sistema!" << endl;
        
        cout << "Deseja Continuar Pesquisando? (S/N)"; cin >> resp;
        cin.ignore(80, '\n');

        resp = toupper(resp);
    }
    continuar();
}


//--------------------------LISTAS DOS ALUNOS---------------------------------------------


void apresentarListas(int N)
{
    system("cls");
    system("clear");
    listar(N);
    cout << endl;
    continuar();
}


//--------------------------MENU PRINCIPAL--------------------------------------------------


int main(void)
{
    int opcao;
    bool sair = false;

    do
    {
        system("cls");
        system("clear");

        // Exibe o menu principal
        cout << "Programa de Registro de Alunos" << endl << endl;

        cout << setfill('*') << setw(33) << "" << endl;
        cout << setfill(' ');
        cout << "*        PAGINA INICIAL         *" << endl;
        cout << setfill('*') << setw(33) << "" << endl;
        cout << setfill(' ');

        cout << setfill('*') << setw(33) << "" << endl;
        cout << setfill(' ');
        cout << "*      (1) Cadastrar            *" << endl;
        cout << "*      (2) Pesquisar            *" << endl;
        cout << "*      (3) Lista de Alunos      *" << endl;
        cout << "*      (4) Lista de Aprovados   *" << endl;
        cout << "*      (5) Lista de Reprovados  *" << endl;
        cout << "*      (0) Sair                 *" << endl;
        cout << setfill('*') << setw(33) << "" << endl;
        cout << setfill(' ');
        cout << "Opcao: "; cin >> opcao; cin.ignore(80, '\n');

        switch(opcao)
        {
            case 0: sair = true; break;
            case 1: cadastrar(); break;
            case 2: pesquisa(); break;
            case 3: apresentarListas(0); break;
            case 4: apresentarListas(1); break;
            case 5: apresentarListas(2); break;

            default: cout << "Opcao Invalida!" << endl;
        }
    }while(!sair);

    cout << "Tecle <Enter> para encerrar...";
    cin.get();
    return 0;
}
