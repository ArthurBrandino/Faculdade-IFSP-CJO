//C02EX03C.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float N1, N2, N3, N4, M;

    cout << "Programa Controle de Media Escolar " << endl << endl;

    cout << "Entre com a primeira nota: "; cin >> N1;
    cin.ignore(80, '\n');

    cout << "Entre com a segunda nota: "; cin >> N2;
    cin.ignore(80, '\n');

    cout << "Entre com a terceira nota: "; cin >> N3;
    cin.ignore(80, '\n');

    cout << "Entre com a quarta nota: "; cin >> N4;
    cin.ignore(80, '\n');

    M = (N1 + N2 + N3 + N4)/4;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    if (M >= 5)
        cout << "Aluno esta Aprovado!";
    else
        cout << "Aluno esta Reprovado!";

    cout << endl;
    cout << "Media: " << fixed << setprecision(2) << M << endl << endl;

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
