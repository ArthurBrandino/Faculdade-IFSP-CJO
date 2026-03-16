//C02EX03M.CPP

#include <iostream>
#include <cctype>

using namespace std;

int main(void)
{
    string NOME;
    char SEXO;

    cout << "Programa de Saudacao" << endl << endl;

    cout << "Entre com seu Nome: "; 
    cin >> NOME;
    cin.ignore(80, '\n');

    cout << "Entre com o seu Sexo (M/F): "; 
    cin >> SEXO;
    cin.ignore(80, '\n');

    SEXO = toupper(SEXO);

    if (SEXO == 'M' || SEXO == 'F') {
        if (SEXO == 'M')
            cout << "Ilmo. Sr. " << NOME << endl;
        else
            cout << "Ilma. Sra. " << NOME << endl;
    }
    else {
        cout << "O Sexo informado e Invalido!" << endl;
    }

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
