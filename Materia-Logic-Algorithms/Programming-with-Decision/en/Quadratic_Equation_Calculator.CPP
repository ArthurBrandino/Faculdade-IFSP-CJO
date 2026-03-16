//C02EX03E.CPP

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void)
{
    float A, B, C, DISCRIMINANT, X1, X2;

    cout << "Second Degree Equation Calculation Program" << endl << endl;
    cout << setfill('*') << setw(70) << "" << endl;
    cout << setfill(' ');
    cout << "* A, B, C = coefficients of the quadratic equation (Ax^2 + Bx + C = 0) *" << endl;
    cout << setfill('*') << setw(70) << "" << endl;
    cout << setfill(' ')  << endl;

    cout << "Enter the value of <A> (Ax^2): "; cin >> A;
    cin.ignore(80, '\n');

    cout << "Enter the value of <B> (Bx): "; cin >> B;
    cin.ignore(80, '\n');

    cout << "Enter the value of <C>: "; cin >> C;
    cin.ignore(80, '\n');

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Result" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    if (A != 0)
    {
        DISCRIMINANT = pow(B, 2) - 4 * A * C;

        if (DISCRIMINANT < 0)
        {
            cout << "There is no Real Solution" << endl;
        }
        else
        {
            X1 = (-B + pow(DISCRIMINANT, 0.5)) / (2 * A);

            if (DISCRIMINANT > 0)
            {
                X2 = (-B - pow(DISCRIMINANT, 0.5)) / (2 * A);
                cout << "There are two Real Solutions" << endl;
                cout << "X1 = " << fixed << setprecision(2) << X1 << endl;
                cout << "X2 = " << fixed << setprecision(2) << X2 << endl;
            }
            else
            {
                cout << "There is one Real Solution" << endl;
                cout << "X = " << fixed << setprecision(2) << X1 << endl;
            }
        }
    }
    else
    {
        cout << "The value of <A> = 0, so the equation is not quadratic!" << endl;
    }

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
