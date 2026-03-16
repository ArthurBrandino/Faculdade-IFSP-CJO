//C02EX03C.CPP

#include <iostream>
#include <iomanip>

using namespace std;

int main(void)
{
    float N1, N2, N3, N4, M;

    cout << "School Average Control Program" << endl << endl;

    cout << "Enter the first grade: "; cin >> N1;
    cin.ignore(80, '\n');

    cout << "Enter the second grade: "; cin >> N2;
    cin.ignore(80, '\n');

    cout << "Enter the third grade: "; cin >> N3;
    cin.ignore(80, '\n');

    cout << "Enter the fourth grade: "; cin >> N4;
    cin.ignore(80, '\n');

    M = (N1 + N2 + N3 + N4) / 4;

    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');
    cout << "* " << setw(3) << "Result" << setw(3) << " *" << endl;
    cout << setfill('*') << setw(15) << "" << endl;
    cout << setfill(' ');

    if (M >= 5)
        cout << "Student is Approved!";
    else
        cout << "Student is Failed!";

    cout << endl;
    cout << "Average: " << fixed << setprecision(2) << M << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
