//C02EX03D.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float N1, N2, N3, N4, MD1, NE, MD2;

    cout << "Programa Controle de Media Escolar 2" << endl << endl;

    cout << "Entre com a primeira nota: "; cin >> N1;
    cin.ignore(80, '\n');

    cout << "Entre com a segunda nota: "; cin >> N2;
    cin.ignore(80, '\n');

    cout << "Entre com a terceira nota: "; cin >> N3;
    cin.ignore(80, '\n');

    cout << "Entre com a quarta nota: "; cin >> N4;
    cin.ignore(80, '\n');

    MD1 = (N1 + N2 + N3 + N4)/4;

    if (MD1 >= 7)
    {
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "Aluno esta Aprovado!" << endl;
        cout << "Media: " << fixed << setprecision(2) << MD1 << endl << endl;
    }
    else
    {
        cout << "Entre com a Nota de Exame: "; cin >> NE;
        cin.ignore(80, '\n');
        MD2 = (MD1 + NE)/2;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        if(MD2 >= 5)
            cout << "Aluno Aprovado por Exame!";
        else
            cout << "Aluno esta Reprovado!";
        cout << endl;
        cout << "Media: " << fixed << setprecision(2) << MD2 << endl << endl;
    }

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
