//C03EX03Q.CPP

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main (void){

    float A, R;
    const float PI = 3.14159265;

    cout << "Area of a Circle Calculation Program" << endl << endl;

    cout << "Enter the Radius: "; cin >> R;
    cin.ignore(80, '\n');

    A = PI * pow(R, 2);

    cout << "The Area of the Circle is: " << fixed << setprecision(2) << A << endl << endl;

    cout << "Press <Enter> to exit...";
    cin.get();

    return 0;
}
