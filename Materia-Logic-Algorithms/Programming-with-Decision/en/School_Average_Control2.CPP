//C02EX03D.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float N1, N2, N3, N4, MD1, NE, MD2;

    cout << "School Average Control Program 2" << endl << endl;

    cout << "Enter the first grade: "; cin >> N1;
    cin.ignore(80, '\n');

    cout << "Enter the second grade: "; cin >> N2;
    cin.ignore(80, '\n');

    cout << "Enter the third grade: "; cin >> N3;
    cin.ignore(80, '\n');

    cout << "Enter the fourth grade: "; cin >> N4;
    cin.ignore(80, '\n');

    MD1 = (N1 + N2 + N3 + N4) / 4;

    if (MD1 >= 7)
    {
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "* " << setw(3) << "Result" << setw(3) << " *" << endl;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "Student is Approved!" << endl;
        cout << "Average: " << fixed << setprecision(2) << MD1 << endl << endl;
    }
    else
    {
        cout << "Enter the Exam Grade: "; cin >> NE;
        cin.ignore(80, '\n');
        MD2 = (MD1 + NE) / 2;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        cout << "* " << setw(3) << "Result" << setw(3) << " *" << endl;
        cout << setfill('*') << setw(15) << "" << endl;
        cout << setfill(' ');
        if (MD2 >= 5)
            cout << "Student Approved by Exam!";
        else
            cout << "Student is Failed!";
        cout << endl;
        cout << "Average: " << fixed << setprecision(2) << MD2 << endl << endl;
    }

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
