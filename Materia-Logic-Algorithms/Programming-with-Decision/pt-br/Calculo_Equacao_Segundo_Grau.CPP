//C02EX03E.CPP

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void)
{
    float A, B, C, DELTA, X1, X2;

    cout << "Programa Calculo da Equacao de Segundo Grau" << endl << endl;
    cout << setfill('*') << setw(70) << "" << endl;
    cout << setfill(' ');
    cout << "* A, B, C = coeficientes da equacao quadratica (Ax^2 + Bx + C = 0) *" << endl;
    cout << setfill('*') << setw(70) << "" << endl;
    cout << setfill(' ')  << endl;

    cout << "Entre com o Valor de <A> (Ax^2): "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <B> (Bx): "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Entre com o Valor de <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Resultado" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    if (A != 0)
    {
        DELTA = pow(B, 2) - 4 * A * C;

        if (DELTA < 0)
        {
            cout << "Nao ha Solucao Real" << endl;
        }
        else
        {
            X1 = (-B + pow(DELTA, 0.5)) / (2 * A);

            if (DELTA > 0)
            {
                X2 = (-B - pow(DELTA, 0.5)) / (2 * A);
                cout << "Ha duas Solucoes Reais" << endl;
                cout << "X1 = " << fixed << setprecision(2) << X1 << endl;
                cout << "X2 = " << fixed << setprecision(2) << X2 << endl;
            }
            else
            {
                cout << "Ha uma Solucao Real" << endl;
                cout << "X = " << fixed << setprecision(2) << X1 << endl;
            }
        }
    }
    else
    {
        cout << "O Valor de <A> = 0, assim a equacao nao e do 2º grau!" << endl;
    }

    cout << "Tecle <Enter> para encerrar...";
    cin.get();

    return 0;
}
